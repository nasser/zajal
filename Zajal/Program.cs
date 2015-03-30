using System;
using System.Diagnostics;
using System.Runtime.InteropServices; 

using System.Threading;
using System.IO;

using clojure.lang;

namespace Zajal {
	public class Program {
		[DllImport("__Internal", EntryPoint="mono_get_runtime_build_info")]
		public extern static string GetMonoVersion();

		public static int VersionMajor = 0;
		public static int VersionMinor = 5;
		public static int VersionRevision = 0;
		public static string VersionName = "Nostrand";
		public static string Version { get { return VersionMajor + "." + VersionMinor + "." + VersionRevision + " - " + VersionName; } }

		public static event Func<object> MainThreadLoop;

		public static void SetClojureClassPath(string path) {
			Environment.SetEnvironmentVariable("CLOJURE_LOAD_PATH", path);
			Console.WriteLine ("Set CLOJURE_LOAD_PATH to " + path);
		}

		public static void SetClojureClassPath() {
			SetClojureClassPath(Path.Combine(Path.GetDirectoryName(System.Reflection.Assembly.GetExecutingAssembly ().Location), "Clojure"));
		}

		public static void Main () {
			Console.WriteLine ("Zajal " + Program.Version);
			Console.WriteLine ("Mono " + GetMonoVersion());

			SetClojureClassPath ();

			Console.Write ("Loading Clojure...");
			RT.load ("zajal/repl");
			Console.WriteLine ("OK");

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