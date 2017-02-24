#pragma once
#include <cmath>
namespace lucio {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// —водка дл€ Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	protected: 
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::TextBox^  textBox4;
	private: System::Windows::Forms::TextBox^  textBox5;
	private: System::Windows::Forms::TextBox^  textBox6;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TextBox^  textBox7;
	private: System::Windows::Forms::TextBox^  textBox8;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label6;
	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// “ребуетс€ переменна€ конструктора.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// ќб€зательный метод дл€ поддержки конструктора - не измен€йте
		/// содержимое данного метода при помощи редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->textBox7 = (gcnew System::Windows::Forms::TextBox());
			this->textBox8 = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->pictureBox1->Location = System::Drawing::Point(11, 19);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(300, 200);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(339, 12);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(67, 29);
			this->button1->TabIndex = 1;
			this->button1->Text = L"start";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(416, 13);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(63, 27);
			this->button2->TabIndex = 2;
			this->button2->Text = L"stop";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// timer1
			// 
			this->timer1->Interval = 1;
			this->timer1->Tick += gcnew System::EventHandler(this, &Form1::timer1_Tick);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(339, 58);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(67, 20);
			this->textBox1->TabIndex = 3;
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(339, 84);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(67, 20);
			this->textBox2->TabIndex = 4;
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(339, 110);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(67, 20);
			this->textBox3->TabIndex = 5;
			// 
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(416, 58);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(67, 20);
			this->textBox4->TabIndex = 6;
			// 
			// textBox5
			// 
			this->textBox5->Location = System::Drawing::Point(416, 84);
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(67, 20);
			this->textBox5->TabIndex = 7;
			// 
			// textBox6
			// 
			this->textBox6->Location = System::Drawing::Point(416, 110);
			this->textBox6->Name = L"textBox6";
			this->textBox6->Size = System::Drawing::Size(67, 20);
			this->textBox6->TabIndex = 8;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(318, 58);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(13, 13);
			this->label1->TabIndex = 9;
			this->label1->Text = L"a";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(318, 84);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(15, 13);
			this->label2->TabIndex = 10;
			this->label2->Text = L"w";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(318, 110);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(10, 13);
			this->label3->TabIndex = 11;
			this->label3->Text = L"f";
			// 
			// textBox7
			// 
			this->textBox7->Location = System::Drawing::Point(339, 162);
			this->textBox7->Name = L"textBox7";
			this->textBox7->Size = System::Drawing::Size(67, 20);
			this->textBox7->TabIndex = 12;
			// 
			// textBox8
			// 
			this->textBox8->Location = System::Drawing::Point(339, 188);
			this->textBox8->Name = L"textBox8";
			this->textBox8->Size = System::Drawing::Size(67, 20);
			this->textBox8->TabIndex = 13;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(324, 165);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(9, 13);
			this->label4->TabIndex = 14;
			this->label4->Text = L"i";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(317, 191);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(16, 13);
			this->label5->TabIndex = 15;
			this->label5->Text = L"dt";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->BackColor = System::Drawing::Color::LightCoral;
			this->label6->Font = (gcnew System::Drawing::Font(L"Miramonte", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label6->Location = System::Drawing::Point(12, 2);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(90, 14);
			this->label6->TabIndex = 16;
			this->label6->Text = L"© »ванЎулюгин";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(502, 231);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->textBox8);
			this->Controls->Add(this->textBox7);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox6);
			this->Controls->Add(this->textBox5);
			this->Controls->Add(this->textBox4);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->pictureBox1);
			this->Name = L"Form1";
			this->Text = L"Form1";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
		double x,y,t,i,dt;
		double ax,ay,wx,wy,fx,fy,Tx,Ty; //const
#pragma endregion
	private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
				 Graphics^ gr1 = pictureBox1 -> CreateGraphics();
					 //перемен
					 /* ax = Convert::ToDouble(textBox1->Text);
					 wx = Convert::ToDouble(textBox2->Text);
					 fx = Convert::ToDouble(textBox3->Text);
					 ay = Convert::ToDouble(textBox4->Text);
					 wy = Convert::ToDouble(textBox5->Text);
					 fy = Convert::ToDouble(textBox6->Text); */

					 i = Convert::ToDouble(textBox7->Text);
					 dt = Convert::ToDouble(textBox8->Text);
					 //краски
					 Pen^ red = gcnew Pen(Color::Red);
					 SolidBrush^ black = gcnew SolidBrush(Color::Black);

					 t = t + dt;
					 x = i*ax * sin(wx * t + fx) + 150;
					 y = i*ay * cos(wy * t + fy) + 100;
					 
					 gr1 -> FillEllipse(black,x,y,3,3);
					 gr1 -> DrawLine(red,0,100,300,100);
					 gr1 -> DrawLine(red,150,0,150,200);
			 }
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
			 timer1->Enabled = true;
				Graphics^ gr1 = pictureBox1 -> CreateGraphics();
				gr1->Clear(SystemColors::ButtonHighlight);
				ax = Convert::ToDouble(textBox1->Text);
					 wx = Convert::ToDouble(textBox2->Text);
					 fx = Convert::ToDouble(textBox3->Text);
					 ay = Convert::ToDouble(textBox4->Text);
					 wy = Convert::ToDouble(textBox5->Text);
					 fy = Convert::ToDouble(textBox6->Text);
		 }
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
			 timer1->Enabled = false;
			 // сброс перемен
			 x = 0;
			 y = 0;
			 t = 0;
		 }
};
}

