#pragma once

namespace calc {

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
	private: System::Windows::Forms::Button^  button1;
	protected: 
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::TextBox^  textBox3;

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
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(16, 14);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(29, 19);
			this->button1->TabIndex = 0;
			this->button1->Text = L"+";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			this->button1->MouseCaptureChanged += gcnew System::EventHandler(this, &Form1::button1_MouseCaptureChanged);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(51, 14);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(29, 19);
			this->button2->TabIndex = 1;
			this->button2->Text = L"-";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(86, 14);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(29, 19);
			this->button3->TabIndex = 2;
			this->button3->Text = L"*";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &Form1::button3_Click);
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(121, 14);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(29, 19);
			this->button4->TabIndex = 3;
			this->button4->Text = L"/";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &Form1::button4_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(17, 46);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(132, 20);
			this->textBox1->TabIndex = 4;
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &Form1::textBox1_TextChanged);
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(17, 72);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(132, 20);
			this->textBox2->TabIndex = 5;
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(16, 98);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(99, 20);
			this->textBox3->TabIndex = 6;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(159, 130);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
		double a,b,c,i;
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
				 a = Convert::ToDouble(textBox1->Text);
				 b = Convert::ToDouble(textBox2->Text);
				 c = a + b;
				 i = 1;
				 textBox3->Text = Convert::ToString(c);
			 }
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
				 a = Convert::ToDouble(textBox1->Text);
				 b = Convert::ToDouble(textBox2->Text);
				 c = a - b;
				 i = 2;
				 textBox3->Text = Convert::ToString(c);
		 }
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
				 a = Convert::ToDouble(textBox1->Text);
				 b = Convert::ToDouble(textBox2->Text);
				 c = a * b;
				 i = 3;
				 textBox3->Text = Convert::ToString(c);
		 }
private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
			     a = Convert::ToDouble(textBox1->Text);
				 b = Convert::ToDouble(textBox2->Text);
				 c = a / b;
				 i = 4;
				 textBox3->Text = Convert::ToString(c);
		 }
private: System::Void button1_MouseCaptureChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			 
			 if (i == 1) {
				 if (( textBox1->Text != "") | (textBox2->Text != "")) {
				 a = Convert::ToDouble(textBox1->Text);
				 b = Convert::ToDouble(textBox2->Text);
				 c = a + b;
				 textBox3->Text = Convert::ToString(c);
				 }
				 else {textBox3->Text = "введите числа";}
				 
			 }
			 	 if (i == 2) {
				 a = Convert::ToDouble(textBox1->Text);
				 b = Convert::ToDouble(textBox2->Text);
				 c = a - b;
				 textBox3->Text = Convert::ToString(c);
				 
			 }
				 if (i == 3) {
				 a = Convert::ToDouble(textBox1->Text);
				 b = Convert::ToDouble(textBox2->Text);
				 c = a * b;
				 textBox3->Text = Convert::ToString(c);
				 
			 }
				 if (i == 4) {
				 a = Convert::ToDouble(textBox1->Text);
				 b = Convert::ToDouble(textBox2->Text);
				 c = a / b;
				 textBox3->Text = Convert::ToString(c);
				 
			 }
		 }
};
}

