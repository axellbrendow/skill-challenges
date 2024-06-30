package org.example;

import java.io.Serializable;
import java.time.Instant;
import java.time.temporal.ChronoUnit;
import java.util.HashMap;
import java.util.Map;
import java.util.Objects;
import java.util.function.Function;

class IdempotencyRecord<T> implements Serializable {
  public enum Status {
    INPROGRESS,
    COMPLETED,
    /**
     * This status is never saved to the data store, it only lives in the code
     */
    EXPIRED
  }

  public String idempotencyKey;
  public Status status;
  /**
   * Use this field to invalidate records after some time. Precision: seconds
   * since epoch.
   */
  public Long expirationTimestamp;
  public T result;

  /**
   * Use this field to invalidate records that have been in progress for more than
   * they should. Precision: milliseconds since epoch.
   * <p>This ensures that:</p>
   * <ul>
   * <li>other concurrently executing requests are blocked from starting</li>
   * <li>subsequent requests will be allowed after some time</li>
   * </ul>
   */
  public Long inProgressExpirationTimestamp;

  public boolean isExpired() {
    final var now = Instant.now();
    return now.isAfter(Instant.ofEpochSecond(expirationTimestamp)) ||
      (status == Status.INPROGRESS && now.isAfter(Instant.ofEpochMilli(inProgressExpirationTimestamp)));
  }

  public Status getStatus() {
    return isExpired() ? Status.EXPIRED : status;
  }

  public static <T> IdempotencyRecord<T> inProgress(String idempotencyKey) {
    final var idempotencyRecord = new IdempotencyRecord<T>();
    idempotencyRecord.idempotencyKey = idempotencyKey;
    idempotencyRecord.status = Status.INPROGRESS;
    idempotencyRecord.expirationTimestamp = Instant.now().plus(1, ChronoUnit.DAYS).getEpochSecond();
    idempotencyRecord.inProgressExpirationTimestamp = Instant.now().plus(3, ChronoUnit.HOURS).toEpochMilli();
    return idempotencyRecord;
  }

  @Override
  public String toString() {
    return "IdempotencyRecord{" +
      "idempotencyKey='" + idempotencyKey + '\'' +
      ", status=" + status +
      ", expirationTimestamp=" + expirationTimestamp +
      ", result=" + result +
      ", inProgressExpirationTimestamp=" + inProgressExpirationTimestamp +
      '}';
  }
}

public class IdempotencyDecorator<T, R> extends Decorator<T, R> {
  private Function<T, String> keyGenerator = null;
  private final Map<String, IdempotencyRecord<R>> cache = new HashMap<>();

  public IdempotencyDecorator(Decorator<T, R> prevDecorator) {
    super(prevDecorator);
  }

  public IdempotencyDecorator(Function<T, R> func) {
    super(func);
  }

  public IdempotencyDecorator<T, R> keyGenerator(Function<T, String> keyGenerator) {
    Objects.requireNonNull(keyGenerator);
    this.keyGenerator = keyGenerator;
    return this;
  }

  public Function<T, R> decorate(Function<T, R> function) {
    // https://sourcegraph.com/github.com/aws-powertools/powertools-lambda-java@3440513161818a7bedae3a0558f9ff88cd248af6/-/blob/powertools-idempotency/src/main/java/software/amazon/lambda/powertools/idempotency/internal/IdempotencyHandler.java?L86
    return (value) -> {
      Objects.requireNonNull(keyGenerator);
      final var key = keyGenerator.apply(value);
      var idempotencyRecord = cache.get(key);
      if (idempotencyRecord != null) {
        System.out.printf("Cache entry found. Key: %s | Value: %s\n", key, idempotencyRecord);
        final var status = idempotencyRecord.getStatus();
        if (status == IdempotencyRecord.Status.COMPLETED) {
          return idempotencyRecord.result;
        } else if (status == IdempotencyRecord.Status.INPROGRESS) {
          throw new RuntimeException("Message processing is already in progress");
        }
      }
      idempotencyRecord = IdempotencyRecord.inProgress(key);
      cache.put(key, idempotencyRecord);
      idempotencyRecord.result = function.apply(value);
      idempotencyRecord.status = IdempotencyRecord.Status.COMPLETED;
      cache.put(key, idempotencyRecord);
      return idempotencyRecord.result;
    };
  }

  public static <T, R> IdempotencyDecorator<T, R> of(Decorator<T, R> prevDecorator) {
    return new IdempotencyDecorator<>(prevDecorator);
  }

  public static <T, R> IdempotencyDecorator<T, R> of(Function<T, R> func) {
    return new IdempotencyDecorator<>(func);
  }
}
