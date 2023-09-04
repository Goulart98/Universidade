import java.io.Serializable;
import java.util.Date;
public class Malas extends Artigo implements Serializable {
    private int donos;
    private int dimensao; // 1 normal 2 grande 3 enorme
    private int material; // 1 se for pele, 2 se for pano, etc;
    private Date data; // data de lançamento da coleção
    private int isPremium; // 1 se for premium, 2 se não for



    public Malas (Artigo a, int donos, int dimensao, int material, Date data, int isPremium){
        super(a);

        this.donos = donos;
        this.dimensao = dimensao;
        this.material = material;
        this.data = data;
        this.isPremium = isPremium;
    }

    public Malas(double est, String desc, String marca, String codAlf, double precoBase, Utilizador a,Status status,Transportadora trans, int donos, int dimensao, int material, Date data, int isPremium) {
        super(est, desc, marca, codAlf, precoBase, a,status,trans);

        this.donos = donos;
        this.dimensao = dimensao;
        this.material = material;
        this.data = data;
        this.isPremium = isPremium;
    }



    public int getDonos(){
        return this.donos;
    }

    public void setDonos(int donos){
        this.donos = donos;
    }

    public int getDimensao(){
        return this.dimensao;
    }

    public void setDimensao(int dimensao){
        this.dimensao = dimensao;
    }

    public int getMaterial(){
        return this.material;
    }

    public String getMaterialString(){
        switch (this.material){
            case 1:
                return "Pele";
            case 2:
                return "Tecido";
        }
        return null;
    }

    public void setMaterial(int material){
        this.material = material;
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


    @Override
    public double getPreco() {
        double res = super.getPreco();
        return res - res/this.getDimensao()*1/this.getMaterial();

    }

    public String getInfo() {
        return "Marca:" + this.getMarca() + "\nDescrição: "+ this.getDesc() +  "\nEstado: " + this.getEstString()
                +"\nTamanho:" +this.getDimensao()+"\nMaterial: " +this.getMaterialString()+ "\nPreço: " + this.getPreco() +"\n--------\n";
    }

    @Override
    public String getResumo() {
        return this.getDesc()+ "\t"+ this.getPreco()+"\n";
    }
}
