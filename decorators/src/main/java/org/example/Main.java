package org.example;

// MdcSetAndClearDecorator
// ExecutionStatusDecorator
// ProposalLockDecorator
// Aspects não podem ser ordenados. Apenas com @Order() do Spring ou @DeclarePrecedence mas não é o ideal.

public class Main {
  public static void main(String[] args) {
    final var decoratedFunction = RetryDecorator.of(
      PublishNextActionsDecorator.of(
        FetchUpdatedValueDecorator.of(
          IdempotencyDecorator.of(
            (Integer x) -> {
              System.out.println("value = " + x);
              if (x <= 3)
                throw new RuntimeException();
              return x;
            }
          ).keyGenerator(String::valueOf)
        )
      )
    ).numRetries(5).decorate();

    decoratedFunction.apply(0);
    decoratedFunction.apply(0);
  }
}
