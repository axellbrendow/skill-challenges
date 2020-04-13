package app;

public abstract class Algoritmo {
    public String nome;

    public Algoritmo(String nome) {
        this.nome = nome;
    }

    public void rodar() {
        System.out.println("Rodando " + this.nome + "...");
    }
}