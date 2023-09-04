import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.security.SecureRandom;
import java.util.*;


/** Esta classe controla o funcionamento do projeto. **/

public class Controller {

    /**
     * Método que inicia o projeto.
     **/
    public static void start() throws Exception {
        Loja loja = new Loja();
        Scanner inputScanner = new Scanner(System.in);

        while (true) {
            Menu.clean();
            Menu.menuPrincipal();
            int option = inputScanner.nextInt();
            switch (option) {

                case 7 -> { // Carregar ficheiros
                    Menu.clean();
                    String nomeFich;
                    option = 0;
                    while (1 > option || option > 3) {
                        Menu.menuCarregamento();
                        option = inputScanner.nextInt();
                        Menu.clean();
                    }
                    if (option == 1) nomeFich = "src/bin/config.txt"; //Default
                    else if (option == 0) {  //Sair
                        System.out.println("\nRegressando ao menu Principal\n");
                        Menu.clean();
                        break;
                    } else { //2 <> Carregar de custom path
                        System.out.println("\nPor Favor introduza o caminho do ficheiro\n");
                        nomeFich = inputScanner.nextLine() + inputScanner.nextLine();
                        Menu.clean();
                    }

                    // Proceder ao carregamento

                    try {
                        Parser.parse(loja, nomeFich);
                    } catch (Exception e) {
                        System.out.println("Erro durante o Carregamento do ficheiro\n");
                        pressEnterKeyToContinue();
                        break;
                    }
                    System.out.println("\nCarregamento efetuado\n");
                    loja.printInfo();
                    Menu.clean();
                }

                case 1 -> { // Login
                    Menu.clean();
                    String passe;
                    String username;
                    Menu.menuUsername();
                    username = inputScanner.nextLine()+inputScanner.nextLine();
                    Menu.menuPasse();
                    passe = inputScanner.nextLine();

                        for (int z=0; z<loja.getUtilizadores().size(); z++) {
                            Utilizador user = loja.getUtilizadores().get(z);
                                if (user.checkUser(username,passe)) {
                                    System.out.println("\nLogin realizado com sucesso!");

                                    boolean logged = true;
                                    Encomenda e = new Encomenda(); // guardar o carrinho de compras
                                    String buffer;
                                    //lógica enquanto logged in
                                    while (logged) {

                                        //Menu.LoggedInSucess();
                                        Menu.menuLoggedIn(user);
                                        int o = inputScanner.nextInt();
                                        int b;
                                        switch (o) {
                                            case 1 -> {//comprar
                                                Menu.loggedComprar();
                                                int c = inputScanner.nextInt();
                                                switch (c) {
                                                    case 1-> {//sapatilhas
                                                        Menu.compraSapatilhas(loja.getSapatilhas());
                                                        b = inputScanner.nextInt();
                                                        if (b >= 0 && b < loja.getSapatilhas().size()&& loja.getSapatilhas().get(b).isDisponivel()) { //garante valor valido
                                                            e.adicionarArtigo(loja.getSapatilhas().get(b));
                                                            loja.setPending(loja.getSapatilhas().get(b));
                                                        }//else Menu.cannotBuy();
                                                    }

                                                    case 2->{//tshirts
                                                        Menu.compraTshirts(loja.getTshirts());
                                                        b = inputScanner.nextInt();
                                                        if (b >= 0 && b < loja.getTshirts().size()&&loja.getTshirts().get(b).isDisponivel()) { //garante valor valido
                                                            e.adicionarArtigo(loja.getTshirts().get(b));
                                                            loja.setPending(loja.getTshirts().get(b));
                                                        }//else Menu.cannotBuy();
                                                    }

                                                    case 3-> {//malas
                                                        Menu.compraMalas(loja.getMalas());
                                                        b = inputScanner.nextInt();
                                                        if (b >= 0 && b < loja.getMalas().size()&&loja.getMalas().get(b).isDisponivel()) { //garante valor valido
                                                            e.adicionarArtigo(loja.getMalas().get(b));
                                                            loja.setPending(loja.getMalas().get(b));
                                                        }//else Menu.cannotBuy();
                                                    }

                                                    case 0-> {//voltar
                                                    }
                                                    default-> {
                                                        System.out.println("\nPor favor selecione opção correta ou voltar\n");
                                                    }
                                                }
                                            }
                                            case 2 -> {//vender
                                                Menu.loggedVender();
                                                o = inputScanner.nextInt();
                                                Date data;
                                                Artigo.Status status;
                                                String buf, marca, desc, codAlf;
                                                int i, donos, tamanho, atac, cor, isPremium, padrao, dimensao, material;
                                                double est, precoBase;
                                                Transportadora trans;
                                                switch (o) {
                                                    case 1->{//sapatilhas
                                                        Menu.venderMarca();
                                                        marca = inputScanner.nextLine() + inputScanner.nextLine();
                                                        Menu.VenderDesc();
                                                        desc = inputScanner.nextLine();
                                                        status = Artigo.Status.disponivel;
                                                        Menu.venderEstado();
                                                        i = inputScanner.nextInt();
                                                        est = i * 0.1;
                                                        codAlf = randomString(12); // Código alfanumérico
                                                        Menu.venderPrecoBase();
                                                        precoBase = inputScanner.nextDouble();
                                                        Menu.venderTransportadora(loja);
                                                        buf = inputScanner.nextLine() + inputScanner.nextLine();
                                                        trans = loja.getTransportadora(buf);
                                                        //Especifico de Sapatilhas
                                                        Menu.venderDonos();
                                                        donos = inputScanner.nextInt();
                                                        Menu.venderSapTamanho();
                                                        tamanho = inputScanner.nextInt();
                                                        Menu.venderSapAtacadores();
                                                        atac = inputScanner.nextInt(); // 1 - possuem atacadores, 2 - não possuem atacadores
                                                        Menu.venderSapCor();
                                                        cor = inputScanner.nextInt(); // 1 se for azul, 2 se for verde, etc
                                                        data = new Date(); // data de lançamento da coleção
                                                        Menu.venderPremium();
                                                        isPremium = inputScanner.nextInt();// 1 se for premium, 2 se não for
                                                        Sapatilhas s = new Sapatilhas(est, desc, marca, codAlf, precoBase, user, status, trans, donos, tamanho, atac, cor, data, isPremium);
                                                        loja.adicionarArtigo(s);
                                                        System.out.println("\nSapatilhas colocadas à venda com sucesso!\nA voltar ao menu...\n");
                                                    }
                                                    case 2-> {//t-shirts
                                                        Menu.venderMarca();
                                                        marca = inputScanner.nextLine() + inputScanner.nextLine();
                                                        Menu.VenderDesc();
                                                        desc = inputScanner.nextLine();
                                                        status = Artigo.Status.disponivel;
                                                        Menu.venderEstado();
                                                        i = inputScanner.nextInt();
                                                        est = i * 0.1;
                                                        codAlf = randomString(12); // Código alfanumérico
                                                        Menu.venderPrecoBase();
                                                        precoBase = inputScanner.nextDouble();
                                                        Menu.venderTransportadora(loja);
                                                        buf = inputScanner.nextLine() + inputScanner.nextLine();
                                                        trans = loja.getTransportadora(buf);
                                                        //especifico de T-Shirts
                                                        Menu.venderDonos();
                                                        donos = inputScanner.nextInt();
                                                        Menu.venderTsTamanho();
                                                        tamanho = inputScanner.nextInt();
                                                        Menu.venderTsPadrao();
                                                        padrao = inputScanner.nextInt();

                                                        Tshirts t = new Tshirts(est, desc, marca, codAlf, precoBase, user, status, donos, tamanho, padrao, trans);
                                                        loja.adicionarArtigo(t);
                                                        System.out.println("\nT-shirt colocada à venda com sucesso!\nA voltar ao menu...\n");
                                                    }

                                                    case 3-> {//malas
                                                        Menu.venderMarca();
                                                        marca = inputScanner.nextLine()+inputScanner.nextLine();
                                                        Menu.VenderDesc();
                                                        desc = inputScanner.nextLine();
                                                        status = Artigo.Status.disponivel;
                                                        Menu.venderEstado();
                                                        i = inputScanner.nextInt();
                                                        est = i * 0.1;
                                                        codAlf = randomString(12); // Código alfanumérico
                                                        Menu.venderPrecoBase();
                                                        precoBase = inputScanner.nextDouble();
                                                        Menu.venderTransportadora(loja);
                                                        buf = inputScanner.nextLine() + inputScanner.nextLine();
                                                        trans = loja.getTransportadora(buf);
                                                        //Especifico de Malas
                                                        Menu.venderDonos();
                                                        donos = inputScanner.nextInt();
                                                        Menu.venderMDimensao();
                                                        dimensao = inputScanner.nextInt();
                                                        Menu.venderMMaterial();
                                                        material = inputScanner.nextInt();
                                                        Menu.venderPremium();
                                                        isPremium = inputScanner.nextInt(); // 1 se for premium, 2 se não for
                                                        data = new Date();

                                                        Malas m = new Malas(est, desc, marca, codAlf, precoBase, user, status, trans, donos, dimensao, material, data, isPremium);
                                                        loja.adicionarArtigo(m);
                                                        System.out.println("\nMala colocada à venda com sucesso!\nA voltar ao menu...\n");
                                                    }

                                                    case 0-> {
                                                    }
                                                    default-> {
                                                        System.out.println("\nPor favor selecione opção correta ou voltar\n");
                                                    }
                                                }
                                            }
                                            case 3 -> {//estatisticas
                                                Menu.loggedStats();
                                            }
                                            case 4 -> {//encomendas
                                                Menu.encomendas();
                                                int k = inputScanner.nextInt();
                                                switch (k) {
                                                    case 1 -> {//checkout
                                                        Menu.confirmCheckout(e);
                                                        buffer = inputScanner.nextLine() + inputScanner.nextLine();
                                                        if (buffer.compareToIgnoreCase("y") == 0) {
                                                            loja.addNewEncomenda(e);
                                                            e = new Encomenda();
                                                        }
                                                    }

                                                    case 2 -> {//Cancel
                                                        Menu.cancelEncomenda(e);
                                                        buffer = inputScanner.nextLine() + inputScanner.nextLine();
                                                        if (buffer.compareToIgnoreCase("y") == 0) {
                                                            loja.cancelEncomenda(e);
                                                            e = new Encomenda();
                                                        }
                                                    }
                                                    case 0-> {
                                                    }
                                                    default-> {
                                                        System.out.println("\nPor favor selecione opção correta ou voltar\n");
                                                    }
                                                }
                                            }
                                            case 0 -> {
                                                logged = false;
                                            }
                                            default -> {
                                                System.out.println("\nPor favor selecione opção correta ou sair\n");
                                            }
                                        }
                                    }
                                }else{
                                    if (z+1==loja.getUtilizadores().size()){
                                        System.out.println("\nErro no login\n");
                                        pressEnterKeyToContinue();
                                        break;
                                    }
                                }
                        }

                }

                case 2 -> { // Criar conta
                    Menu.clean();
                    Menu.menuCreationUserEmail();
                    String email = inputScanner.nextLine()+inputScanner.nextLine();
                        while (true) {
                            boolean b = true;
                            for (Utilizador u : loja.getUtilizadores()) {
                                if (u.verificaEmail(email)) {
                                    b = false;
                                    break;
                                }
                            }
                            if (b) break;
                            Menu.menuCreationUserEmailInUse();
                            email = inputScanner.nextLine();
                        }
                        Menu.menuCreationUserPass();
                        String passe = inputScanner.nextLine();
                        Menu.menuCreationUserName();
                        String nome = inputScanner.nextLine();
                        Menu.menuCreationUsername();
                        String username = inputScanner.nextLine();
                        Menu.menuCreationUserMorada();
                        String morada = inputScanner.nextLine();
                        Menu.menuCreationUserNf();
                        String nf = inputScanner.nextLine();
                        int nif = Integer.parseInt(nf);

                        /*  Para verificar que o nif é valido e unico
                        while (!Utilizador.validaNif(nf)){
                            Menu.menuCreationUserNf();
                            nf = inputScanner.nextLine();
                            while (true) {
                                boolean b = true;
                                for (Utilizador u : loja.getUtilizadores()) {
                                    if (u.getNif()==nif) {
                                        b = false;
                                        break;
                                    }
                                }
                                if (b) break;
                                Menu.menuCreationUserNf();
                                nf = inputScanner.nextLine();
                                nif = Integer.parseInt(nf);
                            }
                        }*/

                    Utilizador user = new Utilizador (email, passe, nome, username, morada, nif);

                        loja.addUser(user);

                        //salvarUtilizadores(loja.getUtilizadores(), "src/bin/users.txt"); // Salva em ficheiro users.txt
                        System.out.println("\nConta criada com sucesso!");
                        pressEnterKeyToContinue();
                }

                case 3 ->{
                    loja.printInfo();
                    pressEnterKeyToContinue();
                }

                case 4 -> { // Guardar um objeto
                        Menu.clean();
                        String saveLoc;
                    try {
                        Menu.menuGuardar();
                        saveLoc = inputScanner.nextLine() + inputScanner.nextLine();
                        if (saveLoc.equals("")) saveLoc = "src/bin/save.obj";
                        loja.save(saveLoc);
                        System.out.println("Estado guardado em: " + saveLoc);
                        //loja.printInfo();
                        pressEnterKeyToContinue();
                    } catch (Exception guard) {
                        guard.printStackTrace();
                        System.out.println("Erro em: Guardar\n");
                        pressEnterKeyToContinue();
                    }
                }

                case 5 -> { // Carregar um objeto
                        Menu.clean();
                        String loadLoc = "";
                        while (1 > option || option > 2) {
                            Menu.menuCarregar();
                            option = inputScanner.nextInt();
                            Menu.clean();
                        }
                        if (option == 2) break;
                        else {
                            Menu.menuCarregar2();
                            loadLoc = inputScanner.nextLine() + inputScanner.nextLine();
                            if (loadLoc.equals("")) loadLoc = "src/bin/save.obj";
                            loja = new Loja();
                            System.out.println("\nA carregar de: " + loadLoc);
                            try {
                                loja = Loja.load(loadLoc);
                            } catch (Exception e) {
                                System.out.println("Erro a Carregar.");
                            }
                            System.out.println("\nEstado Carregado!\nA voltar ao menu principal...\n");
                            //loja.printInfo();
                            pressEnterKeyToContinue();
                        }
                }
                case 6 -> {
                    boolean transport = true;
                    while (transport) {
                        Menu.createTransportadora();
                        option = inputScanner.nextInt();
                        String nome;
                        double p, m, g, mar;
                        int n;
                        switch (option) {
                            case 1:
                                Menu.cTransNome();
                                nome = inputScanner.nextLine()+inputScanner.nextLine();
                                Menu.cTransPeq();
                                p = inputScanner.nextDouble();
                                Menu.cTransMed();
                                m = inputScanner.nextDouble();
                                Menu.cTransGra();
                                g = inputScanner.nextDouble();
                                Menu.cTransMar();
                                n = inputScanner.nextInt();
                                mar =  (double) n /100;
                                Transportadora trans = new Transportadora(nome, p, m, g, mar);
                                loja.adicionarTransportadora(trans);
                                System.out.println("\nTransportadora criada com sucesso!\n");
                                transport = false;
                                break;

                            case 2:
                                Menu.cTransNomeDelete();
                                inputScanner.nextLine();
                                nome = inputScanner.nextLine();
                                loja.removerTransportadora(nome);
                                transport = false;
                                break;

                            case 0:
                                transport = false;
                                break;

                            default:
                                System.out.println("\nPor Favor selecione uma opção correta.\n");
                                break;

                        }
                    }
                }

                case 0 -> { // Sair
                        System.out.print("Até à próxima!\n");
                        System.exit(0);
                    }
                }
            }
        }

    public static void salvarUtilizadores(List<Utilizador> utilizadores, String arquivo) throws IOException {
        BufferedWriter writer = new BufferedWriter(new FileWriter(arquivo, true));
        for(Utilizador u : utilizadores){
            writer.write("Username: "+u.getUsername() + "; Passe: " + u.getPassUser() + "; Nome: " + u.getNomeUser() + "; Email: " + u.getEmailUser() + "; Morada: " + u.getMorada() + "; Número Fiscal: " + u.getNrFiscal() +"\n");
        }
        writer.close();
    }

    /** Método para esperar pelo input antes de prosseguir o display de menus **/
    private static void pressEnterKeyToContinue() {
        System.out.println("\nPressione Enter para continuar.\n");
        try {
            System.in.read();
        }
        catch (Exception ignored) {
        }
    }

    static String randomString(int len){
        SecureRandom rnd = new SecureRandom();
        final String AB = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        StringBuilder sb = new StringBuilder(len);
        for(int i = 0; i < len; i++)
            sb.append(AB.charAt(rnd.nextInt(AB.length())));
        return sb.toString();
    }
}
