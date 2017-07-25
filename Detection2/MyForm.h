#pragma once
#include"cv.h"
#include"highgui.h"
#include"time.h"
#include"Math.h"

#include<iostream>
#include<fstream>
     
namespace Detection2 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace cv;

	//using namespace std;
	float BGR_average[3] = { 0 };
	int dataNum=0;
	time_t  start;
	float time_total=0;
	VideoCapture cap;
	cv::Point LT, RB;
	Mat Img_ROI;
	float time_data[1900] = {0};
	float BGRData[1900] = {0};
#define PI       3.14159265358979323846 
struct compxReIm { float re, im; };
struct compxATheta { float A,theta;};
	
	std::vector<Rect> faces;
	/// <summary>
	/// MyForm 的摘要
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO:  在此加入建構函式程式碼
			//
		}

	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	protected:
	private: System::Windows::Forms::Button^  Btn_Start;
	private: System::Windows::Forms::Button^  Btn_Stop;
	private: System::Windows::Forms::Timer^  timer_Capture;
	private: System::ComponentModel::IContainer^  components;
	private:bool f_setROI,f_ROI_successed;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  txt_ShowCountDown;

	private: System::Windows::Forms::Button^  Btn_analysis;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Button^  Btn_Detect;
	private:
		/// <summary>
		/// 設計工具所需的變數。
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改
		/// 這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->Btn_Start = (gcnew System::Windows::Forms::Button());
			this->Btn_Stop = (gcnew System::Windows::Forms::Button());
			this->timer_Capture = (gcnew System::Windows::Forms::Timer(this->components));
			this->Btn_Detect = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->txt_ShowCountDown = (gcnew System::Windows::Forms::Label());
			this->Btn_analysis = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(5, 3);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(588, 497);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// Btn_Start
			// 
			this->Btn_Start->Location = System::Drawing::Point(665, 32);
			this->Btn_Start->Name = L"Btn_Start";
			this->Btn_Start->Size = System::Drawing::Size(75, 67);
			this->Btn_Start->TabIndex = 1;
			this->Btn_Start->Text = L"開始";
			this->Btn_Start->UseVisualStyleBackColor = true;
			this->Btn_Start->Click += gcnew System::EventHandler(this, &MyForm::Btn_Start_Click);
			// 
			// Btn_Stop
			// 
			this->Btn_Stop->Location = System::Drawing::Point(780, 32);
			this->Btn_Stop->Name = L"Btn_Stop";
			this->Btn_Stop->Size = System::Drawing::Size(74, 67);
			this->Btn_Stop->TabIndex = 2;
			this->Btn_Stop->Text = L"停止";
			this->Btn_Stop->UseVisualStyleBackColor = true;
			this->Btn_Stop->Click += gcnew System::EventHandler(this, &MyForm::Btn_Stop_Click);
			// 
			// timer_Capture
			// 
			this->timer_Capture->Tick += gcnew System::EventHandler(this, &MyForm::timer_Capture_Tick);
			// 
			// Btn_Detect
			// 
			this->Btn_Detect->Location = System::Drawing::Point(665, 126);
			this->Btn_Detect->Name = L"Btn_Detect";
			this->Btn_Detect->Size = System::Drawing::Size(75, 59);
			this->Btn_Detect->TabIndex = 3;
			this->Btn_Detect->Text = L"偵測";
			this->Btn_Detect->UseVisualStyleBackColor = true;
			this->Btn_Detect->Click += gcnew System::EventHandler(this, &MyForm::Btn_Detect_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(761, 568);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(41, 15);
			this->label1->TabIndex = 4;
			this->label1->Text = L"Time:";
			// 
			// txt_ShowCountDown
			// 
			this->txt_ShowCountDown->AutoSize = true;
			this->txt_ShowCountDown->Location = System::Drawing::Point(808, 568);
			this->txt_ShowCountDown->Name = L"txt_ShowCountDown";
			this->txt_ShowCountDown->Size = System::Drawing::Size(21, 15);
			this->txt_ShowCountDown->TabIndex = 5;
			this->txt_ShowCountDown->Text = L"60";
			// 
			// Btn_analysis
			// 
			this->Btn_analysis->Location = System::Drawing::Point(773, 126);
			this->Btn_analysis->Name = L"Btn_analysis";
			this->Btn_analysis->Size = System::Drawing::Size(80, 58);
			this->Btn_analysis->TabIndex = 7;
			this->Btn_analysis->Text = L"資料分析";
			this->Btn_analysis->UseVisualStyleBackColor = true;
			this->Btn_analysis->Click += gcnew System::EventHandler(this, &MyForm::Btn_analysis_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(665, 232);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(41, 15);
			this->label2->TabIndex = 8;
			this->label2->Text = L"label2";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 15);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1790, 622);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->Btn_analysis);
			this->Controls->Add(this->txt_ShowCountDown);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->Btn_Detect);
			this->Controls->Add(this->Btn_Stop);
			this->Controls->Add(this->Btn_Start);
			this->Controls->Add(this->pictureBox1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
public:void ShowImage(System::Windows::Forms::PictureBox^ PBox, cv::Mat Image)
	{
		Mat image_Temp;
		switch (Image.type())
		{
		case CV_8UC3:
			image_Temp = Image;
			break;
		case CV_8UC1:
			cvtColor(Image, image_Temp, CV_GRAY2RGB);
			break;
		default:
			break;
		}
		System::IntPtr ptr(image_Temp.ptr());
		System::Drawing::Graphics^ graphics = PBox->CreateGraphics();
		System::Drawing::Bitmap^ b = gcnew System::Drawing::Bitmap(image_Temp.cols, image_Temp.rows, image_Temp.step, System::Drawing::Imaging::PixelFormat::Format24bppRgb, ptr);
		System::Drawing::RectangleF rect(0, 0, PBox->Width, PBox->Height);
		graphics->DrawImage(b, rect);
		delete graphics;
	}
private: System::Void Btn_Start_Click(System::Object^  sender, System::EventArgs^  e) {
		cap.open(0);
		cap.set(CV_CAP_PROP_FRAME_WIDTH, 480);
		cap.set(CV_CAP_PROP_FRAME_HEIGHT, 360);
		timer_Capture->Interval =100;
		timer_Capture->Enabled = true;
		timer_Capture->Start();
		
	}
private: System::Void timer_Capture_Tick(System::Object^  sender, System::EventArgs^  e) {
		Mat frame;
		if(cap.isOpened())cap >> frame;
		cv::Rect rect;
		if (f_setROI)
		{
			CascadeClassifier face_cascade;
			Mat frame_gray;
			cv::Rect rect;
			cv::String face_cascade_name = "haarcascade_frontalface_alt.xml";
			if (!face_cascade.load(face_cascade_name))MessageBox::Show("haarcascade_frontalface_alt.xml not exist");
			
			cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
			equalizeHist(frame_gray, frame_gray);
			face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, cv::Size(30, 30));//FPS下降
			for (unsigned int i = 0; i < faces.size(); i++)
			{
				LT.x = faces[i].x; LT.y = faces[i].y;
				RB = { faces[i].x + faces[i].width,faces[i].y + faces[i].height };
				Img_ROI = frame(faces[i]);
				f_setROI = false;
				f_ROI_successed = true;
				start = clock();
			}
		}
		if (f_ROI_successed)
		{	
			Img_ROI = frame(faces[0]);
			int sum = 0;

			for (unsigned int i = 0; i < Img_ROI.cols; i++)
			{
				for (unsigned int j = 0; j < Img_ROI.rows; j++)
						sum = sum + (int)Img_ROI.at<Vec3b>(i, j)[1];
			}
			
	        BGRData[dataNum] = (float)sum / (float)(Img_ROI.rows*Img_ROI.cols);		
			
			dataNum++;	
		}
		
		cv::rectangle(frame, LT, RB, CV_RGB(255, 0, 0));
		ShowImage(pictureBox1, frame);
		time_t end = clock();
		time_total = (float)(end - start) / CLK_TCK;
		
		if (time_total >= 60)
		{
			WriteTxt();
			timer_Capture->Enabled;
			timer_Capture->Stop();
			txt_ShowCountDown->Text = "0";
			f_ROI_successed = false;
		}
	
		if (f_ROI_successed) {
			label2->Text = dataNum.ToString();
			time_data[dataNum] = time_total;
			txt_ShowCountDown->Text = (60 - time_total).ToString();
			
		}
	}

private:void WriteTxt(void)
	{
	
		std::fstream fp_G;
		std::fstream fp_T;	
		fp_G.open("G.txt", std::ios::app);	
		fp_T.open("Time.txt", std::ios::app);
		if ( !fp_G ) {//如果開啟檔案失敗，fp為0；成功，fp為非0
			MessageBox::Show("error Writing txt");
		}
		for (int i = 0; i < dataNum; i++)
		{
		fp_G << BGRData[i] << "\n";
		fp_T << time_data[i] << "\n";
		}
		fp_G.close();
		fp_T.close();
	}
private: System::Void Btn_Detect_Click(System::Object^  sender, System::EventArgs^  e) {
		f_setROI = true;
	}
private: System::Void Btn_Stop_Click(System::Object^  sender, System::EventArgs^  e) {
	f_setROI = false;
	f_ROI_successed = false;
	dataNum = 0;

	timer_Capture->Enabled = false;
	timer_Capture->Stop();
	time_total = 0;

}
private: System::Void Btn_analysis_Click(System::Object^  sender, System::EventArgs^  e) {
	compxReIm *B_compx = new compxReIm[dataNum];
	compxReIm *G_compx = new compxReIm[dataNum];
	compxReIm *R_compx = new compxReIm[dataNum];
	float BGR_average=0;

	for (unsigned int i = 0; i < dataNum; i++)
	{
		BGR_average = BGR_average+BGRData[i]/ dataNum;
	}
	
	for (int i = 0; i < dataNum; i++)//資料減平均,轉成compx
	{
		G_compx[i].re = BGRData[i]- BGR_average;
	}
	
	compxReIm *G_DFT_RI = new compxReIm[dataNum];
	
	DFT(dataNum, G_compx, G_DFT_RI);

	 delete[] G_compx;
	 compxATheta *G_DFT_AT = new compxATheta[dataNum];
	for (unsigned int i = 0; i < dataNum; i++)
	{
		G_DFT_AT[i].A = sqrt(pow(G_DFT_RI[i].re, 2) + pow(G_DFT_RI[i].im, 2));	
	}
}
private:void DFT(int data_no, compxReIm *in_data, compxReIm *out_data)
{

	int m, k;
	float w_cos, w_sin, angle_step, angle;

	angle_step = 2 * PI / data_no;
	for (m = 0; m<data_no; m++)
	{
		out_data[m].re = in_data[0].re;
		out_data[m].im = in_data[0].im;
		for (k = 1; k<data_no; k++)
		{
			angle = (float)m*k*angle_step;
			w_cos = cos(angle);
			w_sin = sin(angle);
			out_data[m].re += in_data[k].re * w_cos - in_data[k].im * w_sin;
			out_data[m].im += in_data[k].re * w_sin + in_data[k].im * w_cos;
		}
	}
}
};
}
