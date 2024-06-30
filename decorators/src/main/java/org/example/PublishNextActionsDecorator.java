package org.example;

import java.util.function.Function;

public class PublishNextActionsDecorator<T, R> extends Decorator<T, R> {
  public PublishNextActionsDecorator(Decorator<T, R> prevDecorator) {
    super(prevDecorator);
  }

  public PublishNextActionsDecorator(Function<T, R> func) {
    super(func);
  }

  public Function<T, R> decorate(Function<T, R> function) {
    return (value) -> {
      final var result = function.apply(value);
      System.out.println("Publishing next actions");
      return result;
    };
  }

  public static <T, R> PublishNextActionsDecorator<T, R> of(Decorator<T, R> prevDecorator) {
    return new PublishNextActionsDecorator<>(prevDecorator);
  }

  public static <T, R> PublishNextActionsDecorator<T, R> of(Function<T, R> func) {
    return new PublishNextActionsDecorator<>(func);
  }
}
