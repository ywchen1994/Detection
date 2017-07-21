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
	float BGRData[1900][3] = {0};
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
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  chart_RGB;
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
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^  legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^  series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->Btn_Start = (gcnew System::Windows::Forms::Button());
			this->Btn_Stop = (gcnew System::Windows::Forms::Button());
			this->timer_Capture = (gcnew System::Windows::Forms::Timer(this->components));
			this->Btn_Detect = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->txt_ShowCountDown = (gcnew System::Windows::Forms::Label());
			this->chart_RGB = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->Btn_analysis = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart_RGB))->BeginInit();
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
			this->label1->Location = System::Drawing::Point(840, 568);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(41, 15);
			this->label1->TabIndex = 4;
			this->label1->Text = L"Time:";
			// 
			// txt_ShowCountDown
			// 
			this->txt_ShowCountDown->AutoSize = true;
			this->txt_ShowCountDown->Location = System::Drawing::Point(898, 568);
			this->txt_ShowCountDown->Name = L"txt_ShowCountDown";
			this->txt_ShowCountDown->Size = System::Drawing::Size(21, 15);
			this->txt_ShowCountDown->TabIndex = 5;
			this->txt_ShowCountDown->Text = L"60";
			// 
			// chart_RGB
			// 
			chartArea1->Name = L"ChartArea1";
			this->chart_RGB->ChartAreas->Add(chartArea1);
			legend1->Name = L"Legend1";
			this->chart_RGB->Legends->Add(legend1);
			this->chart_RGB->Location = System::Drawing::Point(860, 7);
			this->chart_RGB->Name = L"chart_RGB";
			series1->ChartArea = L"ChartArea1";
			series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Spline;
			series1->Color = System::Drawing::Color::Blue;
			series1->Legend = L"Legend1";
			series1->Name = L"B_average";
			series2->ChartArea = L"ChartArea1";
			series2->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Spline;
			series2->Color = System::Drawing::Color::Green;
			series2->Legend = L"Legend1";
			series2->Name = L"G_average";
			series3->ChartArea = L"ChartArea1";
			series3->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Spline;
			series3->Color = System::Drawing::Color::Red;
			series3->Legend = L"Legend1";
			series3->Name = L"R_average";
			this->chart_RGB->Series->Add(series1);
			this->chart_RGB->Series->Add(series2);
			this->chart_RGB->Series->Add(series3);
			this->chart_RGB->Size = System::Drawing::Size(510, 558);
			this->chart_RGB->TabIndex = 6;
			this->chart_RGB->Text = L"chart1";
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
			this->ClientSize = System::Drawing::Size(1405, 622);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->Btn_analysis);
			this->Controls->Add(this->chart_RGB);
			this->Controls->Add(this->txt_ShowCountDown);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->Btn_Detect);
			this->Controls->Add(this->Btn_Stop);
			this->Controls->Add(this->Btn_Start);
			this->Controls->Add(this->pictureBox1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart_RGB))->EndInit();
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
		timer_Capture->Interval =2;
		timer_Capture->Enabled = true;
		timer_Capture->Start();
		start = clock();
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
			for (size_t i = 0; i < faces.size(); i++)
			{
				LT.x = faces[i].x; LT.y = faces[i].y;
				RB = { faces[i].x + faces[i].width,faces[i].y + faces[i].height };
				Img_ROI = frame(faces[i]);
				f_setROI = false;
				f_ROI_successed = true;
			}
		}

		if (f_ROI_successed)
		{

			Img_ROI = frame(faces[0]);
			int sum[3] = { 0 };

			for (int i = 0; i < Img_ROI.cols; i++)
			{
				for (int j = 0; j < Img_ROI.rows; j++)

					for (int k = 0; k < 3; k++)
						sum[k] = sum[k] + (int)Img_ROI.at<Vec3b>(i, j)[k];
			}
			for (int i = 0; i < 3; i++)
			{
				BGR_average[i] = (float)sum[i] / (float)(Img_ROI.rows*Img_ROI.cols);
				BGRData[dataNum][i] = (float)sum[i] / (float)(Img_ROI.rows*Img_ROI.cols);
				
			}
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
		std::fstream fp_R;
		std::fstream fp_G;
		std::fstream fp_B;
		std::fstream fp_T;
		fp_R.open("R.txt", std::ios::app);
		fp_G.open("G.txt", std::ios::app);
		fp_B.open("B.txt", std::ios::app);
		fp_T.open("Time.txt", std::ios::app);
		if (!fp_R || !fp_G || !fp_B) {//如果開啟檔案失敗，fp為0；成功，fp為非0
			MessageBox::Show("error Writing txt");
		}
		for (int i = 0; i < dataNum; i++)
		{
			fp_B << BGRData[i][0]<<"\n";
			fp_G << BGRData[i][1] << "\n";
			fp_R << BGRData[i][2] << "\n";
			fp_T << time_data[i] << "\n";
		}
		fp_B.close();//關閉檔案
		fp_G.close();
		fp_R.close();
		fp_T.close();
	}
private: System::Void Btn_Detect_Click(System::Object^  sender, System::EventArgs^  e) {
		f_setROI = true;
	}
private: System::Void Btn_Stop_Click(System::Object^  sender, System::EventArgs^  e) {
	f_setROI = false;
	f_ROI_successed = false;
	dataNum = 0;
	BGRData[1900][3] = {0};
	timer_Capture->Enabled = false;
	timer_Capture->Stop();
	time_total = 0;

}
private: System::Void Btn_analysis_Click(System::Object^  sender, System::EventArgs^  e) {
	compxReIm *B_compx = new compxReIm[dataNum];
	compxReIm *G_compx = new compxReIm[dataNum];
	compxReIm *R_compx = new compxReIm[dataNum];
	float *BGR_average = new float[3];
	for(unsigned int i=0;i<3;i++)//記算平均
		for (unsigned int j = 0; j < dataNum; j++)
		{
			BGR_average[i] = BGR_average[i]+BGRData[j][i]/ dataNum;
		}
	
	for (int i = 0; i < dataNum; i++)//資料減平均,轉成compx
	{
		B_compx[i].re = BGRData[i][0] - BGR_average[0];
		G_compx[i].re = BGRData[i][1] - BGR_average[1];
		R_compx[i].re = BGRData[i][2] - BGR_average[2];
	}
	delete [] BGR_average;

	compxReIm *B_DFT_RI = new compxReIm[dataNum];compxReIm *G_DFT_RI = new compxReIm[dataNum]; compxReIm *R_DFT_RI = new compxReIm[dataNum];
	
	DFT(dataNum, B_compx, B_DFT_RI);DFT(dataNum, G_compx, G_DFT_RI);DFT(dataNum, R_compx, R_DFT_RI);

	delete[] B_compx; delete[] G_compx; delete[] R_compx;
	compxATheta *B_DFT_AT = new compxATheta[dataNum]; compxATheta *G_DFT_AT = new compxATheta[dataNum]; compxATheta *R_DFT_AT = new compxATheta[dataNum];
	for (unsigned int i = 0; i < dataNum; i++)
	{
		B_DFT_AT[i].A = sqrt(pow(B_DFT_RI[i].re, 2) + pow(B_DFT_RI[i].im, 2));
		B_DFT_AT[i].theta = atan2(B_DFT_RI[i].im, B_DFT_RI[i].re);
		G_DFT_AT[i].A = sqrt(pow(G_DFT_RI[i].re, 2) + pow(G_DFT_RI[i].im, 2));
		G_DFT_AT[i].theta = atan2(G_DFT_RI[i].im, G_DFT_RI[i].re);
		R_DFT_AT[i].A = sqrt(pow(R_DFT_RI[i].re, 2) + pow(R_DFT_RI[i].im, 2));
		R_DFT_AT[i].theta = atan2(R_DFT_RI[i].im, R_DFT_RI[i].re);
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
