package org.example;

import java.util.function.Function;

public class RetryDecorator<T, R> extends Decorator<T, R> {
  private int totalExecutions = 1;

  public RetryDecorator(Decorator<T, R> prevDecorator) {
    super(prevDecorator);
  }

  public RetryDecorator(Function<T, R> func) {
    super(func);
  }

  public RetryDecorator<T, R> numRetries(int numRetries) {
    if (numRetries < 0)
      throw new IllegalArgumentException(String.format("numRetries should be >= 0. Received %d", numRetries));
    this.totalExecutions = 1 + numRetries;
    return this;
  }

  public Function<T, R> decorate(Function<T, R> function) {
    return (value) -> {
      RuntimeException exception = null;
      for (int i = 0; i < totalExecutions; i++) {
        try {
          System.out.printf("Execution %d started\n", i + 1);
          final var result = function.apply(value);
          System.out.printf("Execution %d succeeded\n\n", i + 1);
          return result;
        } catch (Exception e) {
          exception = new RuntimeException(e);
          System.out.printf("Execution %d failed\n\n", i + 1);
        }
      }
      System.out.println("Retries exceeded");
      throw exception;
    };
  }

  public static <T, R> RetryDecorator<T, R> of(Decorator<T, R> prevDecorator) {
    return new RetryDecorator<>(prevDecorator);
  }

  public static <T, R> RetryDecorator<T, R> of(Function<T, R> func) {
    return new RetryDecorator<>(func);
  }
}
