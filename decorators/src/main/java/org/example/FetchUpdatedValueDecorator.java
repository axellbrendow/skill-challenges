package org.example;

import java.util.function.Function;

public class FetchUpdatedValueDecorator extends Decorator<Integer, Integer> {
  private int totalExecutions = 0;

  public FetchUpdatedValueDecorator(Decorator<Integer, Integer> prevDecorator) {
    super(prevDecorator);
  }

  public FetchUpdatedValueDecorator(Function<Integer, Integer> func) {
    super(func);
  }

  public Function<Integer, Integer> decorate(Function<Integer, Integer> function) {
    return (value) -> {
      try {
        return function.apply(totalExecutions == 0 ? value : this.fetchUpdatedValue());
      } finally {
        totalExecutions++;
      }
    };
  }

  private int fetchUpdatedValue() {
    return totalExecutions % 2 == 1 ? totalExecutions - 1 : totalExecutions;
  }

  public static FetchUpdatedValueDecorator of(Decorator<Integer, Integer> prevDecorator) {
    return new FetchUpdatedValueDecorator(prevDecorator);
  }

  public static FetchUpdatedValueDecorator of(Function<Integer, Integer> func) {
    return new FetchUpdatedValueDecorator(func);
  }
}
