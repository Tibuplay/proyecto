package MenuTaller;

public class Menu {

    private static boolean salir= false;

    public static void iniciarMenu() {
        while (!salir) {
            System.out.println("Opciones: ");
            System.out.println("1. Submenú ");
            System.out.println("2. Imprimir perro.");
            System.out.println("3. Salir. ");
            switch (Recibir.recibirInt()) {
                case 1:
                    SubMenu.iniciarSubMenu();
                    break;
                case 2:
                    System.out.println("Perro");
                    break;
                case 3:
                    System.out.println("Adiós");
                    salir = true;
                    break;
                default:
                    System.out.println("Ingrese una de las opciones sugeridas.");
                    break;
            }
        }
    }
}