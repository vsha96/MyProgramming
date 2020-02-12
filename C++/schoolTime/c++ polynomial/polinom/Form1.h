#pragma once
#include <math.h>
#include <vector>

int m = 1;
int i = 0,j = 0;
std::vector<int> x(m); 
std::vector<int> y(m);
std::vector<float> l(m); 
int X = 0,Y = 0; //рисование для timer1

namespace polinom {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
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
	private: System::Windows::Forms::TextBox^  textBox2;
	protected: 
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::Button^  button1;

	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::Button^  button4;
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
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->button4 = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(440, 153);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(40, 20);
			this->textBox2->TabIndex = 13;
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(394, 153);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(40, 20);
			this->textBox1->TabIndex = 12;
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(394, 190);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(95, 31);
			this->button2->TabIndex = 11;
			this->button2->Text = L"point";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->pictureBox1->Location = System::Drawing::Point(12, 12);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(250, 250);
			this->pictureBox1->TabIndex = 10;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Click += gcnew System::EventHandler(this, &Form1::pictureBox1_Click);
			this->pictureBox1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::pictureBox1_MouseClick);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(280, 231);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(95, 31);
			this->button1->TabIndex = 9;
			this->button1->Text = L"start";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(280, 157);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(95, 31);
			this->button3->TabIndex = 14;
			this->button3->Text = L"clear";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &Form1::clear);
			// 
			// timer1
			// 
			this->timer1->Interval = 1;
			this->timer1->Tick += gcnew System::EventHandler(this, &Form1::timer1_Tick);
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(280, 194);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(95, 31);
			this->button4->TabIndex = 15;
			this->button4->Text = L"stop";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &Form1::button4_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(386, 283);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->button1);
			this->Name = L"Form1";
			this->Text = L"Form1";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
				 timer1 -> Enabled= "True";
			 }
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
			 
		 }
private: System::Void pictureBox1_Click(System::Object^  sender, System::EventArgs^  e) {
			 
		 }
private: System::Void pictureBox1_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 Graphics^gr = pictureBox1 -> CreateGraphics();
			 SolidBrush^bt = gcnew SolidBrush(Color::Black);
			 Pen^pen = gcnew Pen(Color::Black,3);
			 x[m-1]= e->X;
			 y[m-1]= e->Y;
			 gr -> FillEllipse(bt,x[m-1]-1,y[m-1]-1,2,2);
			 m++;
			 x.resize(m);
			 y.resize(m);
			 l.resize(m);
		 }
private: System::Void clear(System::Object^  sender, System::EventArgs^  e) {
			 Graphics^gr = pictureBox1 -> CreateGraphics();
			 gr-> Clear(SystemColors::ButtonHighlight);
			 Pen^pen = gcnew Pen(Color::Black,1);
			 for (i=0;i!=m;i++) {
				x[i]=0; y[i]=0; l[i]=0;
			 }
			 Y=0; X=0;
			 //очистка
		 }
private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
			 Graphics^gr = pictureBox1 -> CreateGraphics();
			 SolidBrush^bt = gcnew SolidBrush(Color::Black);
			 Y = 0;
			 /* for (j=0;j!=m;j++){
					 l[j]=1;
					 for (i=0;i!=m;i++){
						 l[j]=l[j]*(X-x[i]);
					 }
					 for (i=0;i!=m;i++){
						 if(i!=j){ l[j] = l[j]/(x[j]-x[i]); }
					 }
				 } 
				 for(j=0;j!=m;j++){ Y = Y + y[j]*l[j]; } */
				 X++;
				 if (X>150){
					timer1 -> Enabled= "False";
				 }
			 gr -> FillEllipse(bt,X-1,Y-1,2,2);
		 }
private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
			 timer1 -> Enabled= "False";
		 }
};
}

