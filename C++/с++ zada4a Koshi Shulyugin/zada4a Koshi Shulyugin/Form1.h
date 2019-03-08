#pragma once
#include <cmath>


double F(double xf){
	return exp(xf*xf/4);
}

double f(double xf){
	return 1/2*xf*exp(xf*xf/4);
}

double fn(double xn, double h){
	return xn + h * F(xn);
}

namespace zada4aKoshiShulyugin {

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


	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Button^  button1;


	private:
		/// <summary>
		/// “ребуетс€ переменна€ конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// ќб€зательный метод дл€ поддержки конструктора - не измен€йте
		/// содержимое данного метода при помощи редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->pictureBox1->Location = System::Drawing::Point(12, 38);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(250, 250);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(12, 9);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(50, 13);
			this->label2->TabIndex = 3;
			this->label2->Text = L"графики";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(123, 8);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(138, 24);
			this->button1->TabIndex = 4;
			this->button1->Text = L"нарисовать графики";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(276, 299);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->pictureBox1);
			this->Name = L"Form1";
			this->Text = L"Form1";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
		int i;
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
				 Graphics^gr1 = pictureBox1 -> CreateGraphics();
				 Pen^black = gcnew Pen(Color::Black,2);
				 Pen^red = gcnew Pen(Color::Red,2);
				 int x0 = 1, h = 1, zoom = 1;
				 for(i=x0;i<250;i+=h){
					 gr1 -> DrawLine(black,-f(i)*zoom+125,i,-f(i+h)*zoom+125,i+1);
				 }
				 /*
				 for(i=x0;i!=250;i+=1){
					 gr1 -> DrawLine(red,-fn(i,h)*zoom+125,i,-fn(i+h,h)*zoom+125,i+1);
				 }
				 */
			 }
};
}

