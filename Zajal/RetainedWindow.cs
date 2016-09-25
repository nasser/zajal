using System;
using System.IO;

using OpenTK;
using OpenTK.Input;
using OpenTK.Graphics;
using OpenTK.Graphics.OpenGL;

namespace Zajal
{
	public class RetainedWindow : GameWindow
	{
		string vertexShaderPath;
		string fragmentShaderPath;
		int program;
		int modelMatrixUniform;
		int projectionMatrixUniform;
		int viewMatrixUniform;
		int positionAttribute;

		int vboPosition, vboPosition2;

		public RetainedWindow (string vertexShaderPath, string fragmentShaderPath) : base(400, 400, GraphicsMode.Default, "hummus", GameWindowFlags.Default, DisplayDevice.Default, 3, 2, GraphicsContextFlags.Default)
		{
			this.vertexShaderPath = vertexShaderPath;
			this.fragmentShaderPath = fragmentShaderPath;
		}

		int LoadShader(string path, ShaderType type)
		{
			int id = GL.CreateShader (type);
			GL.ShaderSource (id, File.ReadAllText (path));
			GL.CompileShader (id);
			Console.WriteLine (GL.GetShaderInfoLog (id));
			return id;
		}

		int CreateProgram(string vertexShaderPath, string fragmentShaderPath)
		{
			int id = GL.CreateProgram ();
			GL.AttachShader (id, LoadShader (vertexShaderPath, ShaderType.VertexShader));
			GL.AttachShader (id, LoadShader (fragmentShaderPath, ShaderType.FragmentShader));
			GL.LinkProgram (id);
			Console.WriteLine (GL.GetProgramInfoLog (id));
			return id;
		}


		protected override void OnLoad (EventArgs e)
		{
			base.OnLoad (e);
			Console.WriteLine ("OpenGL " + GL.GetString (StringName.Version));

			program = CreateProgram (vertexShaderPath, fragmentShaderPath);
			modelMatrixUniform = GL.GetUniformLocation (program, "modelMatrix");
			projectionMatrixUniform = GL.GetUniformLocation (program, "projectionMatrix");
			viewMatrixUniform = GL.GetUniformLocation (program, "viewMatrix");
			positionAttribute = GL.GetAttribLocation (program, "position");

			GL.BindVertexArray (GL.GenVertexArray ());

		 	vboPosition = GL.GenBuffer ();
			Vector2[] vs = new Vector2[] { new Vector2(0.25f, 0), new Vector2(1, 0), new Vector2(0, 1) };
			GL.BindBuffer(BufferTarget.ArrayBuffer, vboPosition);
			GL.BufferData (BufferTarget.ArrayBuffer, (IntPtr)(vs.Length * Vector2.SizeInBytes), vs, BufferUsageHint.DynamicDraw);
//			GL.VertexAttribPointer(positionAttribute, 2, VertexAttribPointerType.Float, false, 0, 0);

			vboPosition2 = GL.GenBuffer ();
			Vector2[] vs2 = new Vector2[] { new Vector2(-0.25f, 0), new Vector2(1, 0), new Vector2(0, 1) };
			GL.BindBuffer(BufferTarget.ArrayBuffer, vboPosition2);
			GL.BufferData (BufferTarget.ArrayBuffer, (IntPtr)(vs2.Length * Vector2.SizeInBytes), vs2, BufferUsageHint.DynamicDraw);
//			GL.VertexAttribPointer(positionAttribute, 2, VertexAttribPointerType.Float, false, 0, 0);

			GL.Enable (EnableCap.Blend);
			GL.Enable (EnableCap.LineSmooth);
			GL.PointSize (4f);
		}
			

		protected override void OnRenderFrame (FrameEventArgs e)
		{
			base.OnRenderFrame (e);
			MakeCurrent ();
			ProcessEvents ();

			// uncomment for non-vbo
//			Vector2[] vs = new Vector2[] { new Vector2(0, 0), new Vector2(1, 0), new Vector2(0, 1) };

			GL.Viewport (0, 0, Width, Height);
			GL.ClearColor (1, 0, 0, 1);
			GL.Clear (ClearBufferMask.ColorBufferBit);
			Matrix4 id = Matrix4.Identity;

			GL.UseProgram (program);

			GL.UniformMatrix4 (projectionMatrixUniform, false, ref id);
			GL.UniformMatrix4 (viewMatrixUniform, false, ref id);
			GL.UniformMatrix4 (modelMatrixUniform, false, ref id);

			Vector2[] vs = new Vector2[] { new Vector2(0.25f, 0), new Vector2(0.9f, 0), new Vector2(0, 0.9f) };
			GL.BindBuffer(BufferTarget.ArrayBuffer, vboPosition);
			GL.BufferData (BufferTarget.ArrayBuffer, (IntPtr)(vs.Length * Vector2.SizeInBytes), vs, BufferUsageHint.StaticDraw);
			GL.VertexAttribPointer(positionAttribute, 2, VertexAttribPointerType.Float, false, 0, 0);

			// uncomment for non-vbo
//			GL.VertexAttribPointer (positionAttribute, 2, VertexAttribPointerType.Float, false, 0, vs);
			GL.EnableVertexAttribArray (positionAttribute);
			GL.DrawArrays (PrimitiveType.Triangles, 0, vs.Length);
			GL.DisableVertexAttribArray (positionAttribute);

			SwapBuffers ();
		}
	}
}

