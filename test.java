import com.huawei.NativeExec;

public class test {
	public static void main(String[] argv) {
		String[] tmp = new String[argv.length - 1];
		for (int i = 1; i < argv.length; ++i) {
			tmp[i - 1] = argv[i];
		}
		int r = NativeExec.execv(argv[0], tmp);
		System.out.println(r);
	}
}
