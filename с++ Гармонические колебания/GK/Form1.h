#pragma once
#include <cmath>
#include <cstdlib>

namespace GK {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	protected: 
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::TextBox^  textBox4;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::PictureBox^  pictureBox2;
	private: System::Windows::Forms::PictureBox^  pictureBox3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label8;
	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox3))->BeginInit();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(684, 61);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(162, 28);
			this->button1->TabIndex = 0;
			this->button1->Text = L"запуск";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(852, 61);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(162, 28);
			this->button2->TabIndex = 1;
			this->button2->Text = L"стоп";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &Form1::timer1_Tick);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(737, 108);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(128, 20);
			this->textBox1->TabIndex = 2;
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(737, 146);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(128, 20);
			this->textBox2->TabIndex = 3;
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(737, 188);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(128, 20);
			this->textBox3->TabIndex = 4;
			// 
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(737, 229);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(128, 20);
			this->textBox4->TabIndex = 5;
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::SystemColors::Control;
			this->pictureBox1->Location = System::Drawing::Point(12, 12);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(600, 400);
			this->pictureBox1->TabIndex = 6;
			this->pictureBox1->TabStop = false;
			// 
			// pictureBox2
			// 
			this->pictureBox2->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->pictureBox2->Location = System::Drawing::Point(12, 470);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(600, 400);
			this->pictureBox2->TabIndex = 7;
			this->pictureBox2->TabStop = false;
			// 
			// pictureBox3
			// 
			this->pictureBox3->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->pictureBox3->Location = System::Drawing::Point(674, 470);
			this->pictureBox3->Name = L"pictureBox3";
			this->pictureBox3->Size = System::Drawing::Size(600, 400);
			this->pictureBox3->TabIndex = 8;
			this->pictureBox3->TabStop = false;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(681, 232);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(33, 13);
			this->label4->TabIndex = 12;
			this->label4->Text = L"фаза";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(681, 191);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(50, 13);
			this->label3->TabIndex = 11;
			this->label3->Text = L"m масса";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(681, 149);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(42, 13);
			this->label2->TabIndex = 10;
			this->label2->Text = L"K жест";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(681, 111);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(28, 13);
			this->label1->TabIndex = 9;
			this->label1->Text = L"Амп";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->label5->Location = System::Drawing::Point(680, 481);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(21, 20);
			this->label5->TabIndex = 13;
			this->label5->Text = L"V";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->label6->Location = System::Drawing::Point(22, 481);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(21, 20);
			this->label6->TabIndex = 14;
			this->label6->Text = L"X";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->label7->Location = System::Drawing::Point(1244, 677);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(21, 20);
			this->label7->TabIndex = 15;
			this->label7->Text = L"X";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->label8->Location = System::Drawing::Point(583, 677);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(19, 20);
			this->label8->TabIndex = 16;
			this->label8->Text = L"T";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1286, 897);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->pictureBox3);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->textBox4);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Name = L"Form1";
			this->Text = L"Form1";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox3))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
		double x,y,v,t;
		double y1;
		double a,k,m,f; //const
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
				 timer1->Enabled = true;
				 Graphics^ gr1 = pictureBox1 -> CreateGraphics();
				 gr1->Clear(SystemColors::Control);
				 Graphics^ gr2 = pictureBox2 -> CreateGraphics();
				 gr2->Clear(SystemColors::ButtonHighlight);
				 Graphics^ gr3 = pictureBox3 -> CreateGraphics();
				 gr3->Clear(SystemColors::ButtonHighlight);
			 }
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
			 timer1->Enabled = false;
			 // сброс перемен
			 x = 0;
			 y = 0;
			 t = 0;
			 v = 0;
		 }
private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
			 // создание методов
					 Graphics^ gr1 = pictureBox1 -> CreateGraphics();
					 Graphics^ gr2 = pictureBox2 -> CreateGraphics();
					 Graphics^ gr3 = pictureBox3 -> CreateGraphics();
					 //перемен
					 a = Convert::ToDouble(textBox1->Text);
					 k = Convert::ToDouble(textBox2->Text);
					 m = Convert::ToDouble(textBox3->Text);
					 f = Convert::ToDouble(textBox4->Text);
					 //краски
					 Pen^ red = gcnew Pen(Color::Red);
					 Pen^ control = gcnew Pen(SystemColors::Control);
					 SolidBrush^ black = gcnew SolidBrush(Color::Black);
					 SolidBrush^ Control = gcnew SolidBrush(SystemColors::Control);

					 t = t + 0.08;
					 y = a * cos(sqrt(k/m) * t + f)* 5;
					 x = t * 20;
					 v = (-a * sin(sqrt(k/m) * t + f) * sqrt(k/m))* 5;
					 y1 = a * cos(sqrt(k/m) * (t - 0.08) + f)* 5;
					
					 gr1 -> FillEllipse(Control,y1+a*5,185,30,30);
					 gr1 -> FillEllipse(black,y+a*5,185,30,30);
					 gr1 -> DrawLine(control,y1+a*5,200,y+a*5,200);
					 gr1 -> DrawLine(red,0,200,y+a*5,200);
					 

					 gr2 -> FillEllipse(black,x,y + 200,3,3);
					 gr2 -> DrawLine(red,0,200,600,200);
					 gr2 -> DrawLine(red,1,1,1,400);
					 gr3 -> FillEllipse(black,x,v + 200,3,3);
					 gr3 -> DrawLine(red,0,200,600,200);
					 gr3 -> DrawLine(red,1,1,1,400);
		 }
};
}

