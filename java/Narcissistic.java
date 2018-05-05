import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;

public class Narcissistic {
	private final ArrayList<Integer> result = new ArrayList<Integer>();
	Narcissistic(int end) {
		for (int i = 101; i < end; i++) {
			Integer num = i;
			int res = 0;
			for (char c:num.toString().toCharArray()) {
				res += Math.pow(Integer.parseInt(String.valueOf(c)), 3);
			}
			if (res == i) result.add(i);
		};
	}


	public void printResult() {
		System.out.format("一共有 %s", result.size());
		System.out.println(Arrays.asList(result));
	}


	
	public static void main (String[] args) {
		Scanner s = new Scanner(System.in);
		System.out.print("输入范围： ");
		int end = s.nextInt();
		s.close();
		Narcissistic a = new Narcissistic(end);
		a.printResult();
	}

}
