import java.io.Serializable;
import java.util.Date;

public class Sapatilhas extends Artigo implements Serializable {

    private int donos;
    private int tamanho;
    private int atac; // 1 - possuem atacadores, 2 - não possuem atacadores
    private int cor; // 1 se for azul, 2 se for verde, etc
    private Date data; // data de lançamento da coleção
    private int isPremium; // 1 se for premium, 2 se não for




    public Sapatilhas ( double est, String desc, String marca, String codAlf, double precoBase, Utilizador a,Status status,Transportadora trans, int donos, int tamanho, int atac, int cor, Date data, int isPremium){
        super(est, desc,marca,codAlf,precoBase,a,status,trans);
        this.donos = donos;
        this.tamanho = tamanho;
        this.atac = atac;
        this.cor = cor;
        this.data = data;
        this.isPremium = isPremium;
    }

    public Sapatilhas(Artigo a, int donos, int tamanho, int atac, int cor, Date data, int isPremium) {
        super(a);
        this.donos = donos;
        this.tamanho = tamanho;
        this.atac = atac;
        this.cor = cor;
        this.data = data;
        this.isPremium = isPremium;
    }

    @Override
    public double getPreco() {
        double res = super.getPreco();
        if (this.donos<=1) return res; //caso seja novo
        else return res-(res/this.donos*this.getEst());// caso seja usado
    }



    public int getDonos(){
        return this.donos;
    }

    public void setDonos(int donos){
        this.donos = donos;
    }

    public int getTamanho(){
        return this.tamanho;
    }

    public void setTamanho(int tamanho){
        this.tamanho = tamanho;
    }

    public int getAtac(){
        return this.atac;
    }

    public void setAtac(int atac){
        this.atac = atac;
    }

    public int getCor(){
        return this.cor;
    }

    public void setCor(int cor){
        this.cor = cor;
    }

    public Date getData(){
        return this.data;
    }

    public void setData(Date data){
        this.data = data;
    }

    public int getPremium(){
        return this.isPremium;
    }

    public void setPremium(int isPremium){
        this.isPremium = isPremium;
    }

    public String getInfo(){

        return "Marca:" + this.getMarca() + "\nDescrição: "+ this.getDesc() +  "\nEstado: " + this.getEstString()
                +"\nTamanho:" +this.getTamanho()+ "\nPreço: " + this.getPreco() +"\n--------\n";
    }

    @Override
    public String getResumo() {
        return this.getDesc()+ "\t"+ this.getPreco()+"\n";
    }

}