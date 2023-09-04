import java.io.*;
import java.util.*;

/** Esta classe funciona como base de dados do projeto e preserva a lógica das encomendas **/

public class Loja implements Serializable {
    private List<Utilizador> utilizadores;
    private List<Artigo> artigos;
    private List<Encomenda> encomendas;

    private List<Transportadora> transportadoras;
    private double imposto;
    private double lucro;
    private double custosDeEncomenda;
    private double custosDeExpedicao;

    public Loja(){
        this.artigos = new ArrayList<>();
        this.encomendas = new ArrayList<>();
        this.utilizadores = new ArrayList<>();
        this.transportadoras = new ArrayList<>();
        this.lucro = 0;
        this.custosDeEncomenda = 0;
        this.custosDeExpedicao = 0;
        this.imposto =0;
    }

    public Loja(double l,double cEn,double cEx,double i){
        this.artigos = new ArrayList<>();
        this.encomendas = new ArrayList<>();
        this.utilizadores = new ArrayList<>();
        this.lucro = l;
        this.custosDeEncomenda = cEn;
        this.custosDeExpedicao = cEx;
        this.imposto =i;
    }


    public Loja(Map<String, Utilizador> utilizadores, Map<Integer, Artigo> artigos, List<Encomenda> encomendas){
        utilizadores = new HashMap<>(utilizadores);
        artigos = new HashMap<>(artigos);
        encomendas = new ArrayList<>(encomendas);
        this.lucro = 0;
        this.custosDeEncomenda = 0;
        this.custosDeExpedicao = 0;
        this.imposto =0;
    }




    /** Método que verifica se um email se encontra registado na base de dados de Utilizadores.
     * Deve retornar true se estiver registado e false caso contrário
     **/

    public boolean isUser(String email){
        return this.getUtilizadores().stream().anyMatch((f->f.emailEquals(email)));
    }

    /**
     * Metodo que Carrega um Estado desde um objeto
     * @param fileName local onde está guardado o objeto
     * @return Estado que foi guardado previamente
     *
     */
    public static Loja load(String fileName) throws IOException, ClassNotFoundException {
        FileInputStream fis = new FileInputStream(fileName);
        ObjectInputStream ois = new ObjectInputStream(fis);
        Loja loaded = (Loja) ois.readObject();
        ois.close();
        fis.close();
        return loaded;
    }

    /** Método para gravar um ficheiro objeto
     * @param fileName local onde sera gravado
     */
    public void save(String fileName) throws IOException {
        FileOutputStream fos = new FileOutputStream(fileName);
        ObjectOutputStream oos = new ObjectOutputStream(fos);
        oos.writeObject(this);
        oos.close();
        fos.close();
    }

    public void adicionarArtigo(Artigo artigo) {
        this.artigos.add(artigo);
    }

    public void removerArtigo(Artigo artigo) {
        this.artigos.remove(artigo);
    }

    public List<Artigo> getArtigos() {
        return this.artigos;
    }

    public void adicionarEncomenda(Encomenda encomenda) {
        this.encomendas.add(encomenda);
    }

    public List<Encomenda> getEncomendas() {
        return this.encomendas;
    }

    public List<Utilizador> getUtilizadores() {
        return this.utilizadores;
    }

    public double getCustosDeEncomenda() {
        return custosDeEncomenda;
    }

    public void setCustosDeEncomenda(double custosDeEncomenda) {
        this.custosDeEncomenda = custosDeEncomenda;
    }

    public double getCustosDeExpedicao() {
        return custosDeExpedicao;
    }

    public void setCustosDeExpedicao(double custosDeExpedicao) {
        this.custosDeExpedicao = custosDeExpedicao;
    }



    public Map<Integer,Sapatilhas> getSapatilhas(){
        Map<Integer,Sapatilhas> res = new HashMap<>();
        int i=0;
        for (Artigo a : this.artigos){
            if(a instanceof Sapatilhas && a.getStatus()== Artigo.Status.disponivel){
                res.put(i++,(Sapatilhas) a);
            }
        }
        return res;
    }

    public Map<Integer,Tshirts> getTshirts() {
        Map<Integer,Tshirts> res = new HashMap<>();
        int i=0;
        for (Artigo a : this.artigos){
            if(a instanceof Tshirts && a.getStatus()== Artigo.Status.disponivel){
                res.put(i++,(Tshirts) a);
            }
        }
        return res;
    }

    public Map<Integer,Malas> getMalas() {
        Map<Integer,Malas> res = new HashMap<>();
        int i=0;
        for (Artigo a : this.artigos){
            if(a instanceof Malas && a.getStatus()== Artigo.Status.disponivel){
                res.put(i++,(Malas) a);
            }
        }
        return res;
    }

    public void addNewEncomenda(Encomenda e) {
        this.encomendas.add(e);
        for (Artigo a :e.getArtigos()){
            a.setVendido();
        }
    }

    public List<Transportadora> getTransportadoras() {
        return this.transportadoras;
    }

    public void addUser(Utilizador user) {
        this.utilizadores.add(user);
    }



    public Transportadora getTransportadora(String buf){
        for (Transportadora t:transportadoras) {
            if(t.getNome().equals(buf)) return t;
        }

        return null;
    }

    public void adicionarTransportadora(Transportadora trans) {
        this.transportadoras.add(trans);
    }

    public void removerTransportadora(String nome) {
        this.transportadoras.removeIf(t -> t.getNome().equals(nome));
    }

    public void printInfo() {
        String sb = "\nNúmero de Transportadoras: " + this.transportadoras.size() +
                "\nNúmero de Artigos: " + this.artigos.size() +
                "\nNúmero de Users: " + this.utilizadores.size() +
                "\nNúmero de Encomendas: " + this.encomendas.size();// +
                //"\nUtilizador que mais faturou: " + getUtilizadorMaisFaturou(utilizadores).getNomeUser();

        System.out.print(sb);
    }

    public Utilizador getUtilizadorMaisFaturou(List<Utilizador> listaUtilizadores) {
        Utilizador utilizadorMaisFaturou = null;
        double maiorFaturamento = 0.0;

        for (Utilizador u : listaUtilizadores) {
            double faturamentoUsuario = 0.0;

            for (Artigo a : u.getHistoricoVendas()) {
                faturamentoUsuario += a.getPreco();
            }

            if (faturamentoUsuario > maiorFaturamento) {
                maiorFaturamento = faturamentoUsuario;
                utilizadorMaisFaturou = u;
            }
        }
        return utilizadorMaisFaturou;
    }

    public Utilizador getUser(String s) {
        for (Utilizador u:utilizadores) {
            if(u.getUsername().equals(s)) return u;

        }
        return null;
    }

    public void setPending(Artigo b) {
        for (Artigo a:artigos) {
            if (a.equals(b)) a.setPending();

        }
    }

    public void cancelEncomenda(Encomenda e) {
        for (Artigo a: e.getArtigos()) {
            for (Artigo b: artigos) {
                if(a.equals(b)) b.setDisponivel();

            }

        }
    }
}
