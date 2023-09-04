import java.io.PrintWriter;
import java.io.Serializable;
import java.nio.file.Files;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.ZoneId;
import java.util.*;
import java.time.LocalDate;
import java.util.concurrent.TimeUnit;

public class Encomenda implements Serializable {
    private ArrayList<Artigo> artigos;
    private Dimensao dimensao;
    private Transportadora transportadora;
    private Date data;
    private LocalDate dataEntrega;
    private EstadoEncomenda estado;

    private double preco;



    public Encomenda(ArrayList<Artigo> artigos, Dimensao dimensao, Transportadora transportadora, Date data, EstadoEncomenda estado){
        this.artigos = artigos;
        this.dimensao = dimensao;
        this.transportadora = transportadora;
        this.data = data;
        this.estado = EstadoEncomenda.pendente;
        this.preco =0;
    }

    public Encomenda(List<Artigo> artigos, Dimensao dimensao, Transportadora transportadora, LocalDate data) {
        this.artigos = new ArrayList<>(artigos);
        this.dimensao = dimensao;
        this.transportadora = transportadora;
        this.data = new Date();
        this.estado = EstadoEncomenda.pendente;
    }

    public Encomenda(){
        this.artigos = new ArrayList<>();
        this.dimensao = null;
        this.transportadora = null;
        this.data = new Date();
        this.estado = null;
    }

    public void adicionarArtigo(Artigo artigo){
        this.artigos.add(artigo);
    }

    public void removerArtigo(Artigo artigo){
        this.artigos.remove(artigo);
    }

    public void devolver(){
        LocalDateTime hoje = LocalDateTime.now();
        LocalDateTime dataLocal = LocalDateTime.ofInstant(this.data.toInstant(), ZoneId.systemDefault());
        LocalDateTime limite = dataLocal.plusHours(48);

        if(this.estado == EstadoEncomenda.expedida){
            System.out.println("Não é possível devolver uma encomenda já expedida.\n");
        }
        else if(hoje.isAfter(limite)){
            System.out.println("O prazo para devolução expirou.\n");
        }
        else{
            this.estado = EstadoEncomenda.devolvida;
            System.out.println("Encomenda devolvida com sucesso.\n");
        }
    }

    public String getResumo() {
        double valor=0;
        int novo=0,usado=0;
        Map<Transportadora,Integer> trans = new HashMap<>();
        StringBuilder res = new StringBuilder();
        for (Artigo a: this.artigos){
            res.append(a.getResumo());

            valor +=a.getPreco();
            if (a.getEst()==1) novo++;
            else usado++;
            //logica para adicionar transportadora
            if (trans.containsKey(a.getTransportadora())){
                trans.computeIfPresent(a.getTransportadora(),(k,v) -> v+1); //incrementa o numero de artigos com det transportadora
            }else trans.putIfAbsent(a.getTransportadora(),1);

        }

        for(Map.Entry<Transportadora,Integer> t: trans.entrySet()){
            Transportadora tr = t.getKey();
            Integer i = t.getValue();
            valor+=tr.calcularPrecoExpedicao(i);//valor
            res.append("\nTransportadora: ").append(tr.getNome()).append("\nNumero Itens: ").append(i).append("\nValor total para transportadora: ").append(tr.calcularPrecoExpedicao(i));
        }
        double taxa= ((0.5*novo)+(0.25*usado));
        res.append("\nTaxa de Satisfação serviço: ").append(taxa).append("\nArtigos novos: ").append(novo).append("\nArtigos usados: ").append(usado);
        valor +=taxa;
        res.append("\n____Valor Total ->   ").append(valor);
        this.setprecoFinal(valor);
        return res.toString();
    }

    private void incrementValueFromKey(Map<Transportadora,Integer> trans,Transportadora key){
        trans.computeIfPresent(key,(k,v)->v+1);
    }

    public void setprecoFinal(double valor){
        this.preco=valor;
    }
    public double getPrecoFinal(){
        return this.preco;
    }
    public double getPrecoFinal(int usado,int novo){
        return this.preco + ((0.5*novo)+(0.25*usado));
    }

    enum Dimensao{
        pequena, media, grande
    }

    enum EstadoEncomenda{
        pendente, finalizada, expedida, devolvida
    }

    public ArrayList<Artigo> getArtigos() {
        return artigos;
    }

    public void setArtigos(ArrayList<Artigo> artigos) {
        this.artigos = artigos;
    }

    public Dimensao getDimensao() {
        return dimensao;
    }

    public void setDimensao(Dimensao dimensao) {
        this.dimensao = dimensao;
    }

    public Transportadora getTransportadora() {
        return transportadora;
    }

    public void setTransportadora(Transportadora transportadora) {
        this.transportadora = transportadora;
    }

    public Date getData() {
        return data;
    }

    public void setData(Date data) {
        this.data = data;
    }

    public EstadoEncomenda getEstado() {
        return estado;
    }

    public void setEstado(EstadoEncomenda estado) {
        this.estado = estado;
    }

    public void agendarEntrega(LocalDate dataEntrega) {
        this.dataEntrega = dataEntrega;
        this.estado = EstadoEncomenda.pendente;
    }

    public void entregar(){
        if(this.estado == EstadoEncomenda.pendente){
            this.estado = EstadoEncomenda.expedida;
            Timer timer = new Timer();
            timer.schedule(new TimerTask() {
                @Override
                public void run() {
                    setEstado(EstadoEncomenda.finalizada);
                }
            }, TimeUnit.DAYS.toMillis(2)); // Passa a finalizado em 2 dias ou seja, as encomendas são entregues em 2 dias
            System.out.println("Encomenda entregue com sucesso.\n");
        }
        else{
            System.out.println("A encomenda já foi expedida ou finalizada.\n");
        }
    }

    public void verificarEstadoEncomenda() {
        if (this.estado == EstadoEncomenda.finalizada) {
            LocalDate dataEntrega = LocalDate.ofInstant(this.data.toInstant(), ZoneId.systemDefault());
            LocalDate dataFinalizacao = dataEntrega.plusDays(1); // X dias após a data de entrega ou seja só aparece finalizada depois de 3 dias
            LocalDate hoje = LocalDate.now();

            if (hoje.isEqual(dataFinalizacao) || hoje.isAfter(dataFinalizacao)) {
                this.estado = EstadoEncomenda.finalizada;
            }
        }
    }

}
