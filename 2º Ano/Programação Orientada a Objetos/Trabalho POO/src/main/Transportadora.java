import java.io.Serializable;

public class Transportadora implements Serializable {

    private final String nome;
    private final double[] vExpedicao; // Valores baseda expedição para encomendas pequenas (1 artigo),

    private final double margemLucro;


    Transportadora(String nome,double pequenas, double medias, double grandes,double margem){
        this.nome = nome;
        this.vExpedicao = new double[]{pequenas, medias, grandes}; // Array inicializado com 3 valores passados como parâmetros
        this.margemLucro = margem;
    }

    public String getNome(){
        return this.nome;
    }

    public double calcularPrecoExpedicao(int numArtigos){
        double valorBase;
        if(numArtigos == 1){
            valorBase = this.vExpedicao[0];
        }
        else if(numArtigos <= 5){
            valorBase = this.vExpedicao[1];
        }
        else valorBase = this.vExpedicao[2];

        // médias (2 a 5 artigos) e
        // grandes (mais que 5 artigos).
        // Factor multiplicativo dos impostos
        double fatorImposto = 1.23;
        return (valorBase * fatorImposto *this.margemLucro+1);
    }
}
