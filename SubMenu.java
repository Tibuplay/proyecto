package MenuTaller;

public class SubMenu {
    private static boolean salir= false;
    public static void iniciarSubMenu() {
        while (!salir) {
            System.out.println("Opciones: ");
            System.out.println("1. Opcion 1.");
            System.out.println("2. Opcion 2.");
            System.out.println("3. Salir. ");
            switch (Recibir.recibirInt()) {
                case 1:
                    System.out.println("Opcion 1.");
                    break;
                case 2:
                    System.out.println("Opcion 2.");
                    break;
                case 3:
                    System.out.println("Cerrando submenú.");
                    salir = true;
                    break;
                default:
                    System.out.println("Ingrese una de las opciones sugeridas.");
                    break;
            }
        }
    }
}
