package br.com.fiapride.main;

import br.com.fiapride.model.Veiculo;

public class SistemaPrincipal {

    public static void main(String[] args) {
        Veiculo v1 = new Veiculo("Guilherme", "CSJ-8E44");
        v1.adicionarCombustivel(50);
        // 
        // 
        v1.consumirCombustivel(100);

        System.out.println(v1);
    }
}
        // 