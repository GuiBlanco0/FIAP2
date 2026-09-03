package br.com.fiapride.model;

public class Veiculo {

    private String dono;
    private String placa;
    private double combustivel;

    public Veiculo(String dono, String placa) {
 * 
        this.dono = dono;
        this.placa = placa;
        this.combustivel = 0;
    }

    public void adicionarCombustivel(double quantidade) {
        if (quantidade <= 0) {
            System.out.println("Erro: a quantidade adicionada deve ser positiva.");
            return;
        }
        this.combustivel += quantidade;
    }

    public void consumirCombustivel(double quantidade) {
        if (quantidade <= 0) {
            System.out.println("Erro: a quantidade consumida deve ser positiva.");
            return;
        }
        if (quantidade > this.combustivel) {
            System.out.println("Erro: combustivel insuficiente para essa operacao.");
            return;
        }
        this.combustivel -= quantidade;
    }

    public String getDono() {
        return dono;
    }

    public String getPlaca() {
        return placa;
    }

    public double getCombustivel() {
        return combustivel;
    }

    @Override
    public String toString() {
        return " Dono: " + dono + " Placa: " + placa + " Gasolina: " + combustivel;
    }
}
