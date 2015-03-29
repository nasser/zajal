using System;
using System.Diagnostics;
using System.Runtime.InteropServices; 

using System.Threading;
using System.IO;

using clojure.lang;
using OpenTK;

namespace Zajal {
	public class Program {
		[DllImport("__Internal", EntryPoint="mono_get_runtime_build_info")]
		public extern static string GetMonoVersion();

		public static event Func<object> MainThreadLoop;

		public static void SetClojureClassPath(string path) {
			Environment.SetEnvironmentVariable("CLOJURE_LOAD_PATH", path);
			Console.WriteLine (path);
		}

		public static void SetClojureClassPath() {
			SetClojureClassPath(Path.Combine(Directory.GetCurrentDirectory(), "Clojure"));
		}

		public static void Main () {
			SetClojureClassPath ();

			RT.load ("zajal/repl");
			((IFn)RT.var("zajal.repl", "start-server").getRawRoot()).invoke(11211);
			IFn ZajalReplEvalFn = (IFn)RT.var("zajal.repl", "eval-queue").getRawRoot();

			MainThreadLoop += ZajalReplEvalFn.invoke;

			Stopwatch watch = new Stopwatch ();
			long targetFrameTime = 16;
			watch.Start ();
			while (true) {
				long start = watch.ElapsedMilliseconds;
				MainThreadLoop ();
				long total = watch.ElapsedMilliseconds - start;
				if(total < targetFrameTime)
					Thread.Sleep ((int)(targetFrameTime - total));
			}
		}
	}
}