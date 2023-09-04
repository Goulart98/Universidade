import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.regex.*;

/** Método que popula um estado **/

public class Parser {
    public static void parse(Loja e, String nomeFich) throws LinhaIncorretaException{
        List<String> linhas = new ArrayList<>();
        try{
            linhas = lerFicheiro(nomeFich);
        } catch (Exception excep){
            System.out.println("Nome de ficheiro errado!");
            System.exit(1);
        }
        for (String l:linhas) {
            String[] tok =l.split(",");
            Date data =new Date();
            switch (tok[0]) {
                case "t" -> {
                    Transportadora trans = new Transportadora(tok[1], Double.parseDouble(tok[2]), Double.parseDouble(tok[3]), Double.parseDouble(tok[4]), Double.parseDouble(tok[5]));
                    e.adicionarTransportadora(trans);
                }
                case "u" -> {
                    Utilizador user = new Utilizador(tok[1], tok[2], tok[3], tok[4], tok[5], Integer.parseInt(tok[6]));
                    e.addUser(user);
                }
                case"s"->{
                    Sapatilhas s = new Sapatilhas(Double.parseDouble(tok[11]),tok[2],tok[1],Controller.randomString(12),Double.parseDouble(tok[3]),e.getUser(tok[4]),
                            Artigo.Status.disponivel,e.getTransportadora(tok[5]),Integer.parseInt(tok[6]),Integer.parseInt(tok[7]),Integer.parseInt(tok[8]),Integer.parseInt(tok[9]),
                            data,Integer.parseInt(tok[10]));
                    e.adicionarArtigo(s);

                }
                case"m"->{

                }
                case"T"->{

                }
            }


        }

    }

    /** Este método lê um ficheiro e transforma-o numa lista **/

    public static List<String> lerFicheiro(String nomeFich) throws IOException{
        List<String> lines;
        try{
            lines = Files.readAllLines(Paths.get(nomeFich), StandardCharsets.UTF_8);
        } catch(IOException exc){
            throw new IOException("Invalid Filename!");
        }
        return lines;
    }
}


