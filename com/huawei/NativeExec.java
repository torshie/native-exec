package com.huawei;

public class NativeExec {
	static {
		System.loadLibrary("native-exec");
	}

	native public static int execv(String path, String[] argv);
	native public static int execvp(String file, String[] argv);
}
