import java.util.*;

/** Classe que gere todos os menus do projeto **/

public class Menu {
    Loja loja;
    public Menu(Loja loja){
        this.loja = loja;
    }

    public static void menuPrincipal(){
        String sb = "______________________ Vintage ____________________\n" + "\n______________ Universidade do Minho ______________\n" +
                "\n1 <> Login (Iniciar sessão)\n2 <> Criar conta\n3 <> Ver estatística\n4 <> Guardar\n5 <> Carregar\n6 <> Criar Transportadora\n7 <> Carregar Ficheiros\n0 <> Sair.\n\n";
        System.out.print(sb);
    }

    public static void compraSapatilhas(Map<Integer,Sapatilhas> sapatilhas) {
        StringBuilder sb = new StringBuilder("______________________ Vintage ____________________\nSapatilhas <>\n\n");
        for (Integer s: sapatilhas.keySet()) {
            sb.append(s).append(" --> ").append(sapatilhas.get(s).getInfo());
        }
        sb.append("\nPor favor introduza o número do Artigo que pretende adicionar ao Cesto: (introduza um número inferior a 0 para cancelar)\n");
        System.out.print(sb);
    }

    public static void compraTshirts(Map<Integer,Tshirts> t){
        StringBuilder sb = new StringBuilder("______________________ Vintage ____________________\nT-Shirts <>\n\n");
        for (Integer s: t.keySet()) {
            sb.append(s).append(" --> ").append(t.get(s).getInfo());
        }
        sb.append("\nPor favor introduza o número do Artigo que pretende adicionar ao Cesto: (introduza um número inferior a 0 para cancelar)\n");
        System.out.print(sb);

    }

    public static void compraMalas(Map<Integer,Malas> t){
        StringBuilder sb = new StringBuilder("______________________ Vintage ____________________\nMalas <>\n\n");
        for (Integer s: t.keySet()) {
            sb.append(s).append(" --> ").append(t.get(s).getInfo());
        }
        sb.append("\nPor favor introduza o número do Artigo que pretende adicionar ao Cesto: (introduza um número inferior a 0 para cancelar)\n");
        System.out.print(sb);

    }

    public static void confirmCheckout(Encomenda e) {
        String sb= "____________________ Resumo Encomenda ____________________\n" + e.getResumo()+"\n";
        System.out.print(sb);
        sb="Deseja confirmar a encomenda?\ny ou n?\n";
        System.out.print(sb);
    }

    public static void cancelEncomenda(Encomenda e) {
        String sb= "____________________ Resumo Encomenda ____________________\n" + e.getResumo();
        System.out.print(sb);
        sb="\n\nDeseja cancelar a encomenda?\n" + "Introduza y para confirmar, qualquer outra tecla para cancelar:\n";
        System.out.print(sb);
    }

    public static void loggedStats() {
    }

    public static void loggedEncomendas() {
    }

    public static void VenderDesc() {
        System.out.print("Insira a Descrição do Artigo:\n");
    }

    public static void venderEstado() {
        System.out.print("Insira um valor de 0 a 10 para categorizar o estado do artigo\n0 -> Muito usado/gasto - 10 -> Novo\n");
    }

    public static void venderMarca() {
        System.out.print("Insira a Marca do Artigo:\n");
    }

    public static void venderPrecoBase() {
        System.out.print("Insira o preço do Artigo:\n");
    }

    public static void venderTransportadora(Loja loja) {
        System.out.print("Transportadoras Disponíveis\n");
        for (Transportadora t: loja.getTransportadoras()) {
            String sb = t.getNome() +"\n";
            System.out.print(sb);
        }

    }

    public static void venderDonos() {
        System.out.print("Insira o número de donos deste Artigo:\n");
    }

    public static void venderSapTamanho() {
        System.out.print("Insira o tamanho destas Sapatilhas:\n");
    }

    public static void venderSapAtacadores() {
        System.out.print("Estas Sapatilhas possuem atacadores?\n1 <> Sim\t2 <> Não\n");
    }

    public static void venderSapCor() {
        System.out.print("Por favor selecione a cor das Sapatilhas\n1 <> Azul\t2 <> Vermelho:\n"); // Adicionar cores?
    }

    public static void venderPremium() {
        System.out.print("Este Artigo é Premium?\n1 <> Sim\t2 <> Não\n");
    }

    public static void venderTsTamanho() {
        System.out.print("Por favor selecione o tamanho da T-Shirt\n1 <> S\t2 <> M\t 3 <> L\t 4 <> XL\n");
    }

    public static void venderTsPadrao() {
        System.out.print("Por favor selecione o padrão da T-Shirt\n1 <> Liso\t2 <> Riscas\t3 <> Palmeiras\n");
    }

    public static void venderMDimensao() {
        System.out.print("Por favor selecione o tamanho da Mala\n1 <> Pequena\t2 <> Média\t 3 <> Grande\n");
    }

    public static void venderMMaterial() {
        System.out.print("Por favor selecione o material da Mala:\n1 <> Pele\t2 <> Pele genuína\t 3 <> Tecido\n");
    }

    public static void createTransportadora() {
        System.out.println("______________________ Menu Transportadora ______________________\n");
        System.out.print("Por favor selecione o que deseja fazer:\n1 <> Criar\t2 <> Eliminar\t0 <> Sair\n");
    }

    public static void cTransNome() {
        System.out.println("______________________ Menu Transportadora ______________________\n");
        System.out.print("Por favor insira o nome da Transportadora:\n");
    }

    public static void cTransPeq() {
        System.out.println("______________________ Menu Transportadora ______________________\n");
        System.out.print("Por favor insira o valor de transportar 1 artigo:\n");
    }

    public static void cTransMed() {
        System.out.println("______________________ Menu Transportadora ______________________\n");
        System.out.print("Por favor insira o valor de transportar até 5 artigos:\n");
    }

    public static void cTransGra() {
        System.out.println("______________________ Menu Transportadora ______________________\n");
        System.out.print("Por favor insira o valor de transportar mais de 5 artigos:\n");
    }

    public static void cTransMar() {
        System.out.println("______________________ Menu Transportadora ______________________\n");
        System.out.print("Por favor insira a margem de lucro da transportadora em percentagem (0% a 100%):\n");
    }

    public static void cTransNomeDelete() {
        System.out.println("______________________ Menu Transportadora ______________________\n");
        System.out.print("Por favor insira o nome da Transportadora a remover:\n");
    }

    public static void cannotBuy() {
        System.out.println("______________________ Vintage ____________________\nSelecionou um item errado, por favor tente novamente.\n");
    }

    public static void menuUsername(){
        System.out.println("______________________ Menu Login ______________________\n");
        System.out.print("Insira o seu username:\n");
    }

    public static void menuPasse() {
        System.out.println("______________________ Menu Login ______________________\n");
        System.out.print("Insira a sua palavra-passe:\n");

    }

    public static void menuLoggedIn(Utilizador user){

        System.out.println("\nBem-vindo à Vintage, " + user.getNomeUser() + "!\n");
        System.out.println("O que pretende fazer?\n\n1 <> Comprar artigos\n2 <> Vender artigos\n3 <> Ver estatística\n4 <> Ver cesto/carrinho\n0 <> Sair\n");


    }

    public static void menuCreationUserEmail(){
        String menu = "\nInsira o email que pretende utilizar:\n";
        System.out.print(menu);
    }

    public static void menuCreationUserPass(){
        String menu = "\nInsira a palavra-passe que pretende utilizar:\n";
        System.out.print(menu);
    }

    public static void menuCreationUserName(){
        String menu = "\nInsira o nome que pretende utilizar:\n";
        System.out.print(menu);
    }

    public static void menuCreationUsername(){
        String menu = "\nInsira o username que pretende utilizar:\n";
        System.out.print(menu);
    }

    public static void menuCreationUserMorada(){
        String menu = "\nInsira a morada que pretende utilizar:\n";
        System.out.print(menu);
    }

    public static void menuCreationUserNf(){
        String menu = "\nInsira o número fiscal que pretende utilizar:\n";
        System.out.print(menu);
    }

    public static void menuCreationUserEmailInUse(){
        String menu = ("\nO email que inseriu já se encontra em uso. Por favor insira outro email:\n");
        System.out.print(menu);
    }

    public static void menuCreationUserNfInUse(){
        String menu = ("\nO número fiscal que inseriu já se encontra em uso. Por favor insira outro email.\n");
        System.out.print(menu);
    }

    public static void loggedComprar() {
        String sb = "______________Vintage______________\n" + "\nQue tipo de artigos procura?\n" +
                "\n1 <> Sapatilhas\n2 <> T-shirts\n3 <> Malas\n\n0 <> Voltar à página inicial.\n";
        System.out.print(sb);


    }

    public static void encomendas() {
        System.out.println("______________Vintage______________\n1 <> Fazer checkout\n2 <> Cancelar encomenda\n\n0 <> Voltar á loja\n");
    }

    public double calcularValorTotal(List<Artigo> artigos) {
        double valorTotal = 0.0;
        for (Artigo artigo : artigos) {
            valorTotal += artigo.getPreco();
        }
        return valorTotal;
    }

    /**
     * Esta função implementa o menu do carrinho de compras, permitindo ao usuário visualizar os itens no seu
     * carrinho de compras, realizar o checkout e pagar pelos itens, atualizando os saldos dos usuários envolvidos
     * na transação e adicionando a encomenda ao histórico de encomendas do usuário. Além disso, a função também
     * permite remover itens individuais do carrinho de compras e voltar ao menu principal.
     */



    // Responsável por permitir as vendas de todos os tipos de artigos

    public static void loggedVender(){
        clean();
        String sb = "______________Vintage______________\n" + "\nQue tipo de artigo pretende vender?\n" +
                "\n1 <> Sapatilhas\n2 <> T-shirts\n3 <> Malas\n\n0 <> Voltar à página inicial.\n";
        System.out.print(sb);

    }

    public static void menuGuardar() {
        String menu= "\nPor Favor introduza a localização e o nome.\n(Deixe em branco para guardar em localização default)\n";
        System.out.print(menu);
    }

    public static void menuCarregamento(){
        String menu =   "\n\n1 <> Carregar ficheiro predefenido(src/bin/log.txt)\n" +
                "2 <> Carregar ficheiro personalizado\n\n0 <> Voltar ao menu Principal\n";
        System.out.print(menu);
    }

    public static void menuCarregar() {
        String menu ="\n1 <> Carregar ficheiro\n2 <> Voltar ao menu Principal\n";
        System.out.print(menu);
    }

    public static void menuCarregar2(){
        String menu= "\nPor Favor introduza a localização e o nome do ficheiro:\n(Deixe em branco para carregar de localização default)\n";
        System.out.print(menu);
    }

    public static void clean(){
        System.out.println(System.lineSeparator().repeat(50));
    }

    private static void pressEnterKeyToContinue() {
        System.out.println("\nPressione enter para continuar\n");
        try {
            System.in.read();
        }
        catch (Exception ignored) {
        }
    }

    public void setLoja(Loja loja) {
    }
}

