using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Runtime.InteropServices; 
using System.Collections.Concurrent;

using System.Threading;
using System.IO;

using clojure.lang;

namespace Zajal {
	public class Program {
		public static ConcurrentDictionary<Keyword, Type> dummy = new ConcurrentDictionary<Keyword, Type> ();
		[DllImport("__Internal", EntryPoint="mono_get_runtime_build_info")]
		public extern static string GetMonoVersion();

		// fighwheel live coding
		public static DateTime StartTime;
		public static Dictionary<string, string> NamespaceHash = new Dictionary<string, string>();
		private static Queue<string> nsLoadQueue = new Queue<string>();

		public static long FrameTime = 0;

		public static int VersionMajor = 0;
		public static int VersionMinor = 5;
		public static int VersionRevision = 0;
		public static string VersionName = "Nostrand";
		public static string Version { get { return VersionMajor + "." + VersionMinor + "." + VersionRevision + " - " + VersionName; } }

		public static event Func<object> MainThreadLoop;

		public static void AppendClojureClassPath(string path) {
			Environment.SetEnvironmentVariable("CLOJURE_LOAD_PATH", Environment.GetEnvironmentVariable("CLOJURE_LOAD_PATH") + Path.PathSeparator + path);
		}

		public static void SetClojureClassPath(string path) {
			Environment.SetEnvironmentVariable("CLOJURE_LOAD_PATH", path);
		}

		public static void SetClojureClassPath() {
			SetClojureClassPath(Path.Combine(Path.GetDirectoryName(System.Reflection.Assembly.GetExecutingAssembly ().Location), "Clojure"));
		}

		public static void Message(string label, object content) {
			Message (label, content, ConsoleColor.White);
		}

		public static void Message(string label, object content, ConsoleColor color) {
			var oldColor = Console.ForegroundColor;
			Console.ForegroundColor = color;
			Console.Write (label + " ");
			Console.ForegroundColor = ConsoleColor.Gray;
			Console.WriteLine (content.ToString());
//			Console.ForegroundColor = oldColor;
			Console.ResetColor ();
		}

		public static void StartRenderLoop()
		{
			Stopwatch watch = new Stopwatch();
			long targetFrameTime = 16;
			watch.Start();
			while (true)
			{
				long start = watch.ElapsedMilliseconds;
				// MainThreadLoop();
				FrameTime = watch.ElapsedMilliseconds - start;
				if (FrameTime < targetFrameTime)
					Thread.Sleep((int)(targetFrameTime - FrameTime));
			}
		}

		public static void Main (string[] args) {
			Message ("Zajal", Program.Version);
			Message ("Mono", GetMonoVersion());

			string watchDirectory = ".";
			string mainNameSpace = "";

			if (args.Length == 1) {
				mainNameSpace = args [0];
			} 

			// clojure
			SetClojureClassPath ();
			AppendClojureClassPath (watchDirectory);
			Message ("Clojure", RT.var("clojure.core", "clojure-version").invoke());

			// fighweel
			StartTime = DateTime.Now;
			Message ("Started", StartTime);

			Message ("Watching", Path.GetFullPath(watchDirectory));
			var fsw = new FileSystemWatcher (watchDirectory);
			fsw.EnableRaisingEvents = true;
			fsw.IncludeSubdirectories = true;
			fsw.Changed += (object sender, FileSystemEventArgs e) => {
				var writeTime = File.GetLastWriteTime(e.FullPath);
				if(writeTime > StartTime && e.FullPath.EndsWith(".clj")) {
					nsLoadQueue.Enqueue(e.FullPath);
				}
			};

			MainThreadLoop += () => {
				while (nsLoadQueue.Count > 0) {
					var path = nsLoadQueue.Dequeue ();
					var ns = path.Replace("./", "").Replace(".clj", "");
					string oldCode;
					if(NamespaceHash.TryGetValue(ns, out oldCode)) {
						// loaded file before
						string newCode = File.ReadAllText(path);
						if(oldCode != newCode) {
							// hashes changed, reload ns
							NamespaceHash.Remove(ns);
							NamespaceHash.Add(ns, newCode);
							Message ("Reloading", ns, ConsoleColor.Green);
							try {
								RT.load (ns);
							} catch (Exception ex) {
								Message("Failed", ex.Message, ConsoleColor.Red);
								Compiler.load(new StringReader(oldCode));
							}
						}
					} else {
						// never loaded file before, load ns
						NamespaceHash.Add(ns, File.ReadAllText(path));
						Message ("Reloading", ns, ConsoleColor.Green);
						try {
							RT.load (ns);
						} catch (Exception ex) {
							Message("Failed", ex.Message, ConsoleColor.Red);
						}
					}
				}

				return null;
			};
				
			// repl 
			// TODO start in mainNameSpace
			RT.load ("zajal/repl");
			((IFn)RT.var("zajal.repl", "start-server").getRawRoot()).invoke(11216);
			IFn ZajalReplEvalFn = (IFn)RT.var("zajal.repl", "eval-queue").getRawRoot();
			MainThreadLoop += ZajalReplEvalFn.invoke;

			// load initial namespace
			if (mainNameSpace.Length > 0) {
				Message ("Loading", mainNameSpace, ConsoleColor.Green);
				RT.load (mainNameSpace);
			}

			// rener loop
			StartRenderLoop();
		}
	}
}