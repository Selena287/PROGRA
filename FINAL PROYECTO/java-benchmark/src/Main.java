import java.io.FileWriter;
import java.io.IOException;
import java.util.HashMap;
import java.util.TreeMap;

public class Main {

    public static void main(String[] args) {

        try {
            FileWriter file = new FileWriter("java_results.csv");

            file.write("language,operation,structure,records,time_ms\n");

            int n = 10000;

            // ================= HASHMAP INSERT =================
            HashMap<Integer, Integer> hashMap = new HashMap<>();

            long start = System.nanoTime();

            for (int i = 0; i < n; i++) {
                hashMap.put(i, i);
            }

            long end = System.nanoTime();
            double time = (end - start) / 1_000_000.0;

            file.write("Java,insert,HashMap," + n + "," + time + "\n");

            // ================= HASHMAP SEARCH =================
            start = System.nanoTime();

            for (int i = 0; i < n; i++) {
                hashMap.get(i);
            }

            end = System.nanoTime();
            time = (end - start) / 1_000_000.0;

            file.write("Java,search,HashMap," + n + "," + time + "\n");

            // ================= TREEMAP INSERT =================
            TreeMap<Integer, Integer> treeMap = new TreeMap<>();

            start = System.nanoTime();

            for (int i = 0; i < n; i++) {
                treeMap.put(i, i);
            }

            end = System.nanoTime();
            time = (end - start) / 1_000_000.0;

            file.write("Java,insert,TreeMap," + n + "," + time + "\n");

            // ================= TREEMAP TRAVERSAL =================
            start = System.nanoTime();

            for (Integer key : treeMap.keySet()) {
                int value = treeMap.get(key);
            }

            end = System.nanoTime();
            time = (end - start) / 1_000_000.0;

            file.write("Java,traversal,TreeMap," + n + "," + time + "\n");

            file.close();

            System.out.println("Benchmark Java completado");
            System.out.println("Archivo generado: java_results.csv");

        } catch (IOException e) {
            System.out.println("Error al escribir archivo");
        }
    }
}