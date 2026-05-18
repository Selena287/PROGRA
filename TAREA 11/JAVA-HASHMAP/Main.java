import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.HashMap;
import java.util.Scanner;

public class Main {

  public static void main(String[] args) {

    HashMap<Integer, Estudiante> estudiantes = new HashMap<>();

    Scanner entrada = new Scanner(System.in);

    int opcion;

    System.out.println("MAURA SELENA VELASQUEZ ORTEGA");
    System.out.println("Carne: 9941-24-14056");

    do {

      System.out.println("\n===== MENU =====");

      System.out.println("1. Cargar CSV");
      System.out.println("2. Buscar estudiante");
      System.out.println("3. Eliminar estudiante");
      System.out.println("4. Mostrar estudiantes");
      System.out.println("5. Mostrar estadisticas");
      System.out.println("6. Salir");

      System.out.print("Seleccione una opcion: ");
      opcion = entrada.nextInt();

      switch (opcion) {

        case 1:

          System.out.print("Ingrese nombre del archivo CSV: ");
          String archivo = entrada.next();

          cargarCSV(estudiantes, archivo);

          break;

        case 2:

          System.out.print("Ingrese student_id: ");
          int buscarId = entrada.nextInt();

          if (estudiantes.containsKey(buscarId)) {

            Estudiante estudiante = estudiantes.get(buscarId);

            System.out.println("\n=== ESTUDIANTE ENCONTRADO ===");

            System.out.println(estudiante);

          } else {

            System.out.println("No existe estudiante.");
          }

          break;

        case 3:

          System.out.print("Ingrese student_id: ");
          int eliminarId = entrada.nextInt();

          if (estudiantes.containsKey(eliminarId)) {

            estudiantes.remove(eliminarId);

            System.out.println("Estudiante eliminado.");

          } else {

            System.out.println("No existe estudiante.");
          }

          break;

        case 4:

          System.out.println("\n=== ESTUDIANTES ACTUALES ===");

          for (Integer key : estudiantes.keySet()) {

            System.out.println("-------------------");

            System.out.println(estudiantes.get(key));
          }

          break;

        case 5:

          System.out.println("\n=== ESTADISTICAS ===");

          System.out.println("Total estudiantes: " + estudiantes.size());

          System.out.println("Estructura utilizada: HashMap<Integer, Estudiante>");

          break;

        case 6:

          System.out.println("Saliendo...");

          break;

        default:

          System.out.println("Opcion invalida");
      }

    } while (opcion != 6);
  }

  public static void cargarCSV(HashMap<Integer, Estudiante> estudiantes,
                               String archivo) {

    try {

      BufferedReader br = new BufferedReader(new FileReader(archivo));

      String linea;

      br.readLine();

      while ((linea = br.readLine()) != null) {

        String[] datos = linea.split(",");

        int studentId = Integer.parseInt(datos[0]);

        String fullName = datos[1];

        String career = datos[2];

        int semester = Integer.parseInt(datos[3]);

        double gpa = Double.parseDouble(datos[4]);

        int skillScore = Integer.parseInt(datos[5]);

        if (!estudiantes.containsKey(studentId)) {

          Estudiante e = new Estudiante(
                  studentId,
                  fullName,
                  career,
                  semester,
                  gpa,
                  skillScore
          );

          estudiantes.put(studentId, e);

          System.out.println("Estudiante insertado: " + fullName);

        } else {

          System.out.println("Estudiante duplicado: " + studentId);
        }
      }

      br.close();

      System.out.println("Archivo CSV cargado correctamente.");

    } catch (IOException e) {

      System.out.println("Error al abrir archivo.");
    }
  }
}