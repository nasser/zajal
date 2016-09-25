using System;
using OpenTK;
using OpenTK.Input;
using OpenTK.Graphics;
using OpenTK.Graphics.OpenGL;
using clojure.lang;


namespace Zajal {
	public class Window : GameWindow {
		public Var LoadFnVar, DrawFnVar, FocusedChangedFnVar, VisibleChangedFnVar, TitleChangedFnVar, IconChangedFnVar,
		DisposedFnVar, ClosedFnVar, ResizeFnVar, WindowBorderChangedFnVar, MouseWheelFnVar,
		MouseMoveFnVar, MouseUpFnVar, MouseDownFnVar, MouseEnterFnVar, MouseLeaveFnVar, KeyUpFnVar, KeyPressFnVar,
		KeyDownFnVar, WindowStateChangedFnVar, MoveFnVar;

		public Window(string ns = "zajal.window", int width = 400, int height = 400, int glMajor = 4, int glMinor = 1) :
		base(width, height, GraphicsMode.Default, "hummus", GameWindowFlags.Default, DisplayDevice.Default, glMajor, glMinor, GraphicsContextFlags.Default) {
			Title = "Namespace Window - " + ns;

			DrawFnVar = RT.var(ns, "on-draw");
			LoadFnVar = RT.var(ns, "on-load");
			FocusedChangedFnVar = RT.var(ns, "on-focused-changed");
			VisibleChangedFnVar = RT.var(ns, "on-visible-changed");
			TitleChangedFnVar = RT.var(ns, "on-title-changed");
			IconChangedFnVar = RT.var(ns, "on-icon-changed");
			DisposedFnVar = RT.var(ns, "on-disposed");
			ClosedFnVar = RT.var(ns, "on-closed");
			ResizeFnVar = RT.var(ns, "on-resize");
			WindowBorderChangedFnVar = RT.var(ns, "on-window-border-changed");
			MouseWheelFnVar = RT.var(ns, "on-mouse-wheel");
			MouseMoveFnVar = RT.var(ns, "on-mouse-move");
			MouseUpFnVar = RT.var(ns, "on-mouse-up");
			MouseDownFnVar = RT.var(ns, "on-mouse-down");
			MouseEnterFnVar = RT.var(ns, "on-mouse-enter");
			MouseLeaveFnVar = RT.var(ns, "on-mouse-leave");
			KeyUpFnVar = RT.var(ns, "on-key-up");
			KeyPressFnVar = RT.var(ns, "on-key-press");
			KeyDownFnVar = RT.var(ns, "on-key-down");
			WindowStateChangedFnVar = RT.var(ns, "on-window-state-changed");
			MoveFnVar = RT.var(ns, "on-move");

			Visible = true;
			VSync = VSyncMode.On;

			MakeCurrent ();
			DoOnLoad ();
			Program.MainThreadLoop += DoRenderFrame;
		}

		void TryInvoke(Var v) {
			if(v.isBound) {
				try {
					((IFn)v.getRawRoot ()).invoke ();
				} catch (Exception ex) {
					Console.WriteLine (ex.ToString ());
				}
			}
		}

		void TryInvoke(Var v, object a) {
			if(v.isBound) {
				try {
					((IFn)v.getRawRoot ()).invoke (a);
				} catch (Exception ex) {
					Console.WriteLine (ex.ToString ());
				}
			}
		}

		void TryInvoke(Var v, object a, object b) {
			if(v.isBound) {
				try {
					((IFn)v.getRawRoot ()).invoke (a, b);
				} catch (Exception ex) {
					Console.WriteLine (ex.ToString ());
				}
			}
		}

//		 protected override void OnRenderFrame (FrameEventArgs e) {
		public object DoRenderFrame () {
			MakeCurrent ();
			ProcessEvents ();
			TryInvoke (DrawFnVar, this);
			SwapBuffers ();
			return null;
		}

//		protected override void OnLoad (EventArgs e) {
		protected void DoOnLoad () {
			TryInvoke (LoadFnVar, this);
		}

		protected override void OnFocusedChanged (EventArgs e) {
			TryInvoke (FocusedChangedFnVar);
		}

		protected override void OnVisibleChanged (EventArgs e) {
			TryInvoke (VisibleChangedFnVar);
		}

		protected override void OnTitleChanged (EventArgs e) {
			TryInvoke (TitleChangedFnVar);
		}

		protected override void OnIconChanged (EventArgs e) {
			TryInvoke (IconChangedFnVar);
		}

		protected override void OnDisposed (EventArgs e) {
			TryInvoke (DisposedFnVar);
		}

		protected override void OnClosed (EventArgs e) {
			TryInvoke (ClosedFnVar);
		}

		/*
    protected override void OnClosing (EventArgs e) {
      if(ClosingFnVar.isBound)
        ((IFn)ClosingFnVar.getRawRoot ()).invoke();

    }
    */

		protected override void OnResize (EventArgs e) {
			TryInvoke (ResizeFnVar);
		}

		protected override void OnWindowBorderChanged (EventArgs e) {
			TryInvoke (WindowBorderChangedFnVar);
		}

		protected override void OnMouseWheel (MouseWheelEventArgs e) {
			TryInvoke (MouseWheelFnVar, e);
		}

		protected override void OnMouseMove (MouseMoveEventArgs e) {
			TryInvoke (MouseMoveFnVar, e);
		}

		protected override void OnMouseUp (MouseButtonEventArgs e) {
			TryInvoke (MouseUpFnVar, e);
		}

		protected override void OnMouseDown (MouseButtonEventArgs e) {
			TryInvoke (MouseDownFnVar, e);
		}

		protected override void OnMouseEnter (EventArgs e) {
			TryInvoke (MouseEnterFnVar);
		}

		protected override void OnMouseLeave (EventArgs e) {
			TryInvoke (MouseLeaveFnVar);
		}

		protected override void OnKeyUp (KeyboardKeyEventArgs e) {
			TryInvoke (KeyUpFnVar, e);
		}

		protected override void OnKeyPress (KeyPressEventArgs e) {
			TryInvoke (KeyPressFnVar, e);
		}

		protected override void OnKeyDown (KeyboardKeyEventArgs e) {
			TryInvoke (KeyDownFnVar, e);
		}

		protected override void OnWindowStateChanged (EventArgs e) {
			TryInvoke (WindowStateChangedFnVar);
		}

		protected override void OnMove (EventArgs e) {
			TryInvoke (MoveFnVar);
		}
	}
}