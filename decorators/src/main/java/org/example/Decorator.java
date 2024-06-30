package org.example;

import java.lang.reflect.Modifier;
import java.util.function.Function;

public abstract class Decorator<T, R> {
  private Decorator<T, R> prevDecorator;
  private Function<T, R> func;

  public Decorator(Decorator<T, R> prevDecorator) {
    this.prevDecorator = prevDecorator;
    this.validateStaticFactoryMethods();
  }

  public Decorator(Function<T, R> func) {
    this.func = func;
    this.validateStaticFactoryMethods();
  }

  protected abstract Function<T, R> decorate(Function<T, R> func);

  public Function<T, R> decorate() {
    return decorate(prevDecorator != null ? prevDecorator.decorate() : func);
  }

  private void validateStaticFactoryMethods() {
    var hasFactoryFromDecorator = false;
    var hasFactoryFromFunction = false;
    final var mySubclass = this.getClass();
    for (final var method : mySubclass.getDeclaredMethods()) {
      if (
        !Modifier.isPublic(method.getModifiers())
          || !Modifier.isStatic(method.getModifiers())
          || !method.getReturnType().equals(mySubclass)
          || !method.getName().equals("of")
          || !(method.getParameterCount() == 1)
      ) continue;

      hasFactoryFromDecorator = hasFactoryFromDecorator || (
        method.getParameterTypes()[0].equals(Decorator.class)
      );
      hasFactoryFromFunction = hasFactoryFromFunction || (
        method.getParameterTypes()[0].equals(Function.class)
      );
    }

    if (hasFactoryFromDecorator && hasFactoryFromFunction) return;

    throw new IllegalStateException(
      """
        Define static factory methods for your decorator:
        public static <T, R> $Subclass<T, R> of(Decorator<T, R> prevDecorator) {
          return new $Subclass<>(prevDecorator);
        }
        public static <T, R> $Subclass<T, R> of(Function<T, R> func) {
          return new $Subclass<>(func);
        }
        """.replace("$Subclass", mySubclass.getSimpleName())
    );
  }
}
