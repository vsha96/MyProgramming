#pragma once
#include <math.h>
#include <vector>
double a[8] = {0.5 , 1 , 1.25 , 1.5 , 1.75 , 2 , 2.3 , 3};
double F(double xf) { return (2*xf-1)*pow(xf,0.5); }
double difF(double xf) { return (-1+6*xf)/(2*sqrt(xf)); }
double x,f;
int i;


namespace difcpolinomomlagranja {

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
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	protected: 
	private: System::Windows::Forms::PictureBox^  pictureBox2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox2))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->pictureBox1->Location = System::Drawing::Point(12, 12);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(250, 250);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Click += gcnew System::EventHandler(this, &Form1::pictureBox1_Click);
			// 
			// pictureBox2
			// 
			this->pictureBox2->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->pictureBox2->Location = System::Drawing::Point(280, 12);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(250, 250);
			this->pictureBox2->TabIndex = 1;
			this->pictureBox2->TabStop = false;
			this->pictureBox2->Click += gcnew System::EventHandler(this, &Form1::pictureBox2_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(277, -4);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(113, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"график производной";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(9, -4);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(90, 13);
			this->label2->TabIndex = 3;
			this->label2->Text = L"график функции";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(555, 278);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->pictureBox1);
			this->Name = L"Form1";
			this->Text = L"Form1";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox2))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void pictureBox1_Click(System::Object^  sender, System::EventArgs^  e) {
				 Graphics^gr = pictureBox1 -> CreateGraphics();
				 SolidBrush^bt = gcnew SolidBrush(Color::Black);
				 Pen^pen = gcnew Pen(Color::Black,1);
				 gr -> DrawLine(pen,0,150,250,150);
				 gr -> DrawLine(pen,0,0,0,250);
				 for (x=0;x<1;x+=0.0001){
					 f = F(x);
					 gr -> FillEllipse(bt,250*x,150-f*150,2,2);
				 }
			 }
	private: System::Void pictureBox2_Click(System::Object^  sender, System::EventArgs^  e) {
				/* Graphics^gr = pictureBox2 -> CreateGraphics();
				 SolidBrush^bt = gcnew SolidBrush(Color::Black);
				 Pen^pen = gcnew Pen(Color::Black,1);
				 gr -> DrawLine(pen,0,150,250,150);
				 gr -> DrawLine(pen,0,0,0,250);
				 for (x=0.0001;x<1;x+=0.0001){
					 f = difF(x);
					 gr -> FillEllipse(bt,250*x,150-f*10,2,2);
				 }*/

				 Graphics^gr = pictureBox2 -> CreateGraphics();
				 SolidBrush^bt = gcnew SolidBrush(Color::Black);
				 Pen^pen = gcnew Pen(Color::Black,1);
				 gr -> DrawLine(pen,0,150,250,150);
				 gr -> DrawLine(pen,0,0,0,250);
				 for(i=0;i<6;i++){
					 for (x=a[i];x<a[i+2];x+=0.0001){
						 f = F(a[i+1])*( (2*x-a[i]*a[i+2]) / ((a[i+1]-a[i])*(a[i+1]-a[i+2])) );
						 gr -> FillEllipse(bt,20*(x-a[i]),150-f*10,2,2);
					 }
				 }
			 }

};
}

