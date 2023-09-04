import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;


/** Classe que define os parâmetros de um Utilizador **/

public class Utilizador implements Serializable{
    protected List<Artigo> historicoVendas;
    protected double totalFaturado;

    private String nome;
    private String username;
    private String email;
    private String passe;
    private String morada;
    private int nf; // Número fiscal

    public Utilizador(Utilizador c){
        passe = c.getPassUser();
        email = c.getEmailUser();
        nome = c.getNomeUser();
        morada = c.getMorada();
        nf = c.getNrFiscal();
        this.historicoVendas = new ArrayList<>();
    }

    public Utilizador(String emailUser, String passUser, String nomeUser, String usern, String add, int nrFiscal) {
        email = emailUser;
        passe = passUser;
        nome = nomeUser;
        username = usern;
        morada = add;
        nf = nrFiscal;
        this.historicoVendas = new ArrayList<>();
    }


    public String getPassUser(){
        return this.passe;
    }

    public void setPassUser(String passe){
        this.passe = passe;
    }

    public String getUsername(){
        return this.username;
    }

    public void setUsername(String username){
        this.username = username;
    }

    public String getEmailUser(){
        return this.email;
    }

    public void setEmailUser(String email){
        this.email = email;
    }

    public String getNomeUser(){
        return this.nome;
    }

    public void setNomeUser(String nome){
        this.nome = nome;
    }

    public String getMorada(){
        return this.morada;
    }

    public void setMorada(String morada){
        this.morada = morada;
    }

    public Integer getNrFiscal(){
        return this.nf;
    }

    public void setNrFiscal(int nf){
        this.nf = nf;
    }

    public boolean emailEquals(String email){
        return this.email.equals(email);
    }

    public boolean verificaEmail(String email) {
        return this.email.equals(email);
    }

    public int getNif() {return this.nf;}

    public static boolean validaNif(String nif)
    {
        try
        {
            final int max=9;
            if (!nif.matches("[0-9]+") || nif.length()!=max) return false;
            int checkSum=0;
            //calcula a soma de controlo
            for (int i=0; i<max-1; i++){
                checkSum+=(nif.charAt(i)-'0')*(max-i);
            }
            int checkDigit=11-(checkSum % 11);
            if (checkDigit>=10) checkDigit=0;
            return checkDigit==nif.charAt(max-1)-'0';
        }
        catch (Exception e)
        {
            return false;
        }
        finally
        {
        }
    }



    public List<Artigo> getHistoricoVendas(){
        return historicoVendas;
    }

    public void setHistoricoVendas(List<Artigo> historico){
        this.historicoVendas = historico;
    }

    public double getTotalFaturado(){
        return totalFaturado;
    }

    public void setTotalFaturado(double totalF){
        this.totalFaturado = totalF;
    }

    public boolean checkUser(String username, String passe) {
        return this.username.equals(username) && this.passe.equals(passe);
    }
}