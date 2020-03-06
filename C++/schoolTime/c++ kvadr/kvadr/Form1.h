#pragma once
#include <math.h>
#include <iostream>
#include <vector>

float x[5], y[5];
int X[5], Y[5]; //точки на pictureBox


namespace kvadr {
	//using namespace std;
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для Form1
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
		/// Освободить все используемые ресурсы.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ComboBox^  comboBox1;
	protected: 
	private: System::Windows::Forms::Button^  button1;


	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::Button^  button3;

	private:
		/// <summary>
		/// Требуется переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Обязательный метод для поддержки конструктора - не изменяйте
		/// содержимое данного метода при помощи редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->button3 = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// comboBox1
			// 
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(4) {L"линия", L"степень", L"экспонента", L"логарифм"});
			this->comboBox1->Location = System::Drawing::Point(280, 13);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(95, 21);
			this->comboBox1->TabIndex = 0;
			this->comboBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::comboBox1_SelectedIndexChanged);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(280, 231);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(95, 31);
			this->button1->TabIndex = 1;
			this->button1->Text = L"start";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->pictureBox1->Location = System::Drawing::Point(12, 12);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(250, 250);
			this->pictureBox1->TabIndex = 4;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Click += gcnew System::EventHandler(this, &Form1::pictureBox1_Click);
			this->pictureBox1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::pictureBox1_MouseClick);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(280, 115);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(95, 31);
			this->button2->TabIndex = 5;
			this->button2->Text = L"point";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(280, 78);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(40, 20);
			this->textBox1->TabIndex = 6;
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(326, 78);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(40, 20);
			this->textBox2->TabIndex = 7;
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(280, 194);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(95, 31);
			this->button3->TabIndex = 8;
			this->button3->Text = L"clear";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &Form1::button3_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(389, 278);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->comboBox1);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		//int m; //massive vector
		int i;
		int d;
		long int a,b; //коэффицент
		float e1,e2x,e2y,e3; // линейная index 0
		//float A; // степенная index 1
		
		

	private: System::Void pictureBox1_Click(System::Object^  sender, System::EventArgs^  e) {

			 }
private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void comboBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
		 }

private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
			 Graphics^gr = pictureBox1 -> CreateGraphics();
			 //gr-> Clear(SystemColors::ButtonHighlight);
			 Pen^pen = gcnew Pen(Color::Black,2);
			 SolidBrush^bt = gcnew SolidBrush(Color::Black);
			 e1 = 0; e2x = 0; e2y = 0; e3 = 0;
			 if(comboBox1->SelectedIndex==0){
				for(i=0;i!=5;i++){e1 += x[i]*y[i]; e2x = e2x + x[i]; e2y = e2y + y[i]; e3 += x[i]*x[i];}
				//e1 = e1*5; // e1* на колличество точек
				//e2 = e2x*e2y;
				a = (5*e1-e2x*e2y)/(5*e3-e2x*e2x);
				b = (e2y-a*e2x)/5;
			 }
			 if(comboBox1->SelectedIndex==1){
				//передается функция y=a*x^b
				//превращается ln(y) = ln(a)+ b*ln(x) -> Y = A+ b*X
				 for(i=0;i!=5;i++){ x[i] = log(x[i]); y[i]=log(y[i]);
					e1 = e1 + x[i]*y[i]; e2x = e2x + x[i]; e2y = e2y + y[i]; e3 = e3 + x[i]*x[i];
				 }
				 a = (5*e1-e2x*e2y)/(5*e3-e2x*e2x);
				 b = (e2y-a*e2x)/5;
			 }

			 if(comboBox1->SelectedIndex==2){
				//передается функция y=a*e^(b*x)
				//превращается ln(y) = ln(a)+ b*x -> Y = A+ b*x
				 for(i=0;i!=5;i++){ y[i] = log(y[i]);
					e1 = e1 + x[i]*y[i]; e2x = e2x + x[i]; e2y = e2y + y[i]; e3 = e3 + x[i]*x[i];
				 }
				 b = (5*e1-e2x*e2y)/(5*e3-e2x*e2x);
				 a = (e2y-a*e2x)/5;
			 }

			 if(comboBox1->SelectedIndex==3){
				//передается функция y=a+b*ln(x)
				//превращается y = a+ b*X
				 //E = 2.71=exp(1.0);
				 for(i=0;i!=5;i++){ y[i]= exp(y[i]);
					e1 = e1 + x[i]*y[i]; e2x = e2x + x[i]; e2y = e2y + y[i]; e3 = e3 + x[i]*x[i]; 
				 }
				 a = (5*e1-e2x*e2y)/(5*e3-e2x*e2x);
				 b = (e2y-a*e2x)/5;
			 }
			 gr -> DrawLine(pen,0,b,250,a*250+b);
			 
		 }
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
			 Graphics^gr = pictureBox1 -> CreateGraphics();
			 SolidBrush^bt = gcnew SolidBrush(Color::Black);
			 Pen^pen = gcnew Pen(Color::Black,3);
			 x[i]=Convert::ToInt64(textBox1->Text);
			 y[i]=Convert::ToInt64(textBox2->Text);
			 X[i]=x[i];
			 Y[i]=y[i];
			 gr -> FillEllipse(bt,X[i]-1,Y[i]-1,2,2);
			 i++;
		 }
private: System::Void pictureBox1_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 Graphics^gr = pictureBox1 -> CreateGraphics();
			 SolidBrush^bt = gcnew SolidBrush(Color::Black);
			 Pen^pen = gcnew Pen(Color::Black,3);
			 x[i]= e->X;
			 y[i]= e->Y;
			 X[i]=x[i];
			 Y[i]=y[i];
			 gr -> FillEllipse(bt,X[i]-1,Y[i]-1,2,2);
			 i++;
		 }
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
			 Graphics^gr = pictureBox1 -> CreateGraphics();
			 gr-> Clear(SystemColors::ButtonHighlight);
			 Pen^pen = gcnew Pen(Color::Black,1);
			 for (i=0;i=!5;i++) {
				x[i]=0; y[i]=0; X[i]=0; Y[i]=0;
			 }
			 e1=0;e2x=0;e2y=0;e3=0;a=0;b=0;
			 //gr -> DrawLine(pen,125,0,125,250);
			 //gr -> DrawLine(pen,0,125,250,125);
		 }
};
}

