import java.lang.reflect.Field;

public class DllManager {
    public static void initDependentLibraries() throws Exception {
        // Get this file's path
        String libraryPath = new java.io.File(
                DllManager.class.getProtectionDomain().getCodeSource().getLocation().toURI().getPath()).getParentFile()
                .getAbsolutePath() + "/libs";
        // Add library path
        Field userPathsField = ClassLoader.class.getDeclaredField("usr_paths");
        userPathsField.setAccessible(true);
        String[] paths = (String[]) userPathsField.get(null);
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < paths.length; i++) {
            if (libraryPath.equals(paths[i])) {
                continue;
            }
            sb.append(paths[i]).append(';');
        }
        sb.append(libraryPath);
        System.setProperty("java.library.path", sb.toString());
        final Field sysPathsField = ClassLoader.class.getDeclaredField("sys_paths");
        sysPathsField.setAccessible(true);
        sysPathsField.set(null, null);
        // Find all of dll files
        String[] dllFiles = new java.io.File(libraryPath).list();
        // Sort the dll files by creation time
        java.util.Arrays.sort(dllFiles, new java.util.Comparator<String>() {
            @Override
            public int compare(String s1, String s2) {
                java.io.File f1 = new java.io.File(libraryPath, s1);
                java.io.File f2 = new java.io.File(libraryPath, s2);
                return Long.compare(f1.lastModified(), f2.lastModified());
            }
        });
        // load dll files
        for (String dllFile : dllFiles) {
            if (dllFile.endsWith(".dll") || dllFile.endsWith(".so")) {
                System.load(new java.io.File(libraryPath, dllFile).getAbsolutePath());
            }
        }
    }
}