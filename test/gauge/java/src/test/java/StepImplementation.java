import com.thoughtworks.gauge.Step;
import com.thoughtworks.gauge.datastore.ScenarioDataStore;
import com.thoughtworks.gauge.Gauge;

import libraryT.scripts.LibraryT;
import libraryT.scripts.Point;

import static org.assertj.core.api.Assertions.assertThat;

public class StepImplementation {
    static {
        try {
            DllManager.initDependentLibraries();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    @Step("<x>加<y>等于<z>")
    public void add(int x, int y, int z) {
        int _z = LibraryT.MathAdd(x, y);
        assertThat(_z).isEqualTo(z);
    }

    @Step("点（<x1>, <y1>）到点（<x2>, <y2>）的距离的距离为<distance>")
    public void distance(int x1, int y1, int x2, int y2, double distance) {
        Point c1 = Point.create(x1, y1);
        Point c2 = Point.create(x2, y2);
        double _distance = LibraryT.MathDistance(c1, c2);
        Gauge.writeMessage("距离为%s", String.valueOf(_distance));
        assertThat(_distance).isEqualTo(distance);
    }

    @Step("<x>的哈希值为<hash>")
    public void hash(double x, String hash) {
        java.math.BigInteger _hash = LibraryT.MathHash(x, null);
        Gauge.writeMessage("哈希值为%s", String.valueOf(_hash));
        assertThat(String.valueOf(_hash)).isEqualTo(hash);
    }

    @Step("<x>使用算法<y>的开方为<sqrt>")
    public void sqrt(double x, int y, double sqrt) {
        double _sqrt = LibraryT.MathSqrt((float) x, y);
        Gauge.writeMessage("开方结果为%s", String.valueOf(_sqrt));
        assertThat(Math.abs(_sqrt - sqrt) < 0.01).isTrue();
    }
}