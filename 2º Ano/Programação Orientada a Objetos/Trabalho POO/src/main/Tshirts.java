import java.io.Serializable;

public class Tshirts extends Artigo implements Serializable {

    private int donos;
    private int tamanho; // 1 - S, 2 - M, 3 - L, 4 - XL
    private int padrao; // 1 - liso, 2 - riscas, 3 - palmeiras


    public Tshirts( double est, String desc, String marca, String codAlf, double precoBase, Utilizador a, Status status,int donos, int tamanho, int padrao, Transportadora transportadora) {
        super(est, desc, marca, codAlf, precoBase, a, status,transportadora);
        this.donos = donos;
        this.tamanho = tamanho;
        this.padrao = padrao;
    }

    public Tshirts(Artigo a, int av, int donos, int tamanho, int padrao, Transportadora transportadora) {
        super(a);
        this.donos = donos;
        this.tamanho = tamanho;
        this.padrao = padrao;
    }
    // falta desconto de 50% (as lisas nunca têm desconto)



     public int getDonos(){
        return this.donos;
    }

    public void setDonos(int donos){
        this.donos = donos;
    }

    public int getTamanho(){
        return this.tamanho;
    }

    public String getTamanhoString(){
        switch (this.getTamanho()){
            case 1:
                return "S";
            case 2:
                return "M";
            case 3:
                return "L";
            case 4:
                return "XL";
        }
        return null;
    }

    public void setTamanho(int tamanho){
        this.tamanho = tamanho;
    }

    public int getPadrao(){
        return this.padrao;
    }

    public void setPadrao(int atac){
        this.padrao = padrao;
    }

    public String getPadraoString(){
        switch (this.getTamanho()){
            case 1:
                return "Liso";
            case 2:
                return "Riscas";
            case 3:
                return "Palmeiras";
        }
        return null;
    }

    @Override
    public double getPreco() {
        double res= super.getPreco();
        if (this.padrao==1) return res;
        else if (this.getEst()!=1) {
            return res*0.5;
        }else return res;

    }

    public String getInfo() {
        return "Marca: " + this.getMarca() + "\tDescrição: "+ this.getDesc() +  "\nEstado: " + this.getEstString()
                +"\tTamanho:" +this.getTamanhoString()+"\nPadrao: " +this.getPadraoString()+ "\nPreço: " + this.getPreco() +"\n--------\n";
    }
    @Override
    public String getResumo() {
        return this.getDesc()+ "\t"+ this.getPreco()+"\n";
    }
}
