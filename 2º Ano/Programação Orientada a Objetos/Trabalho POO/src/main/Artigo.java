import java.io.Serializable;

public class Artigo implements Serializable {
    private Status status;
    private double est; //1 -> novo 0-> lixo
    private String desc; // Descrição do artigo
    private String marca; // Se for 1 é Adidas, se for 2 é nike, etc...
    private String codAlf; // Código alfanumérico
    private double precoBase;

    private Transportadora transportadora;

    private final Utilizador vendedor;


    //falta desconto mas acho que é na transportadora

    public Artigo ( double est, String desc, String marca, String codAlf, double precoBase, Utilizador a,Status status,Transportadora trans){

        this.est = est;
        this.desc = desc;
        this.marca = marca;
        this.codAlf = codAlf;
        this.precoBase = precoBase;
        this.vendedor = a;
        this.status = status;
        this.transportadora = trans;

    }

    public Artigo(Artigo c) {
        est = c.getEst();
        desc = c.getDesc();
        marca = c.getMarca();
        codAlf = c.getCodAlf();
        precoBase = c.getPreco();
        vendedor = c.getVendedor();
        status = c.getStatus();
        transportadora = c.getTransportadora();
    }

    public Transportadora getTransportadora() {
        return this.transportadora;
    }

    public void setTransportadora(Transportadora t) {
        this.transportadora = t;
    }


    /**
    Devolve o estado do artigo entre 0.0 e 1.0
    @return 1 se novo,0 se completamente usado
    */
    public double getEst(){
        return this.est;
    }

    public void setEst(double est){
        this.est = est;
    }


    public String getEstString(){
        if (this.est==1) return "Novo";
        else return "Usado";
    }




    public Status getStatus() {
        return this.status;
    }

    public void setVendido(){
        this.status = Status.vendido;
    }

    public void setDisponivel() {
        this.status = Status.disponivel;
    }

    public String getResumo() {
        return this.getDesc()+ "\t"+ this.getPreco()+"\n";
    }

    public boolean isDisponivel() {
        return this.status == Status.disponivel;
    }

    public void setPending() {
        this.status = Status.pendente;
    }

    enum Status{
        disponivel, vendido, pendente
    }

    public String getDesc(){
        return this.desc;
    }

    public void setDesc(String desc){
        this.desc = desc;
    }

    public String getMarca(){
        return this.marca;
    }

    public void setMarca(String marca){
        this.marca = marca;
    }

    public String getCodAlf(){
        return this.codAlf;
    }

    public void setCodAlf(String codAlf){
        this.codAlf = codAlf;
    }

    public double getPreco(){
        return this.precoBase;
    }

    public void setPreco(double preco){
        this.precoBase = preco;
    }

    public Utilizador getVendedor(){
        return this.vendedor;
    }

}
