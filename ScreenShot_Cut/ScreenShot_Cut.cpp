#include <opencv2/opencv.hpp>
#include <iostream>
#include <iomanip>
#include <io.h>
#include <string>
#include <cmath> 
using namespace cv;
using namespace std;
#define ImgSizeCows 800 //원본 이미지 가로길이
#define ImgSizeRows 547 //원본 이미지 세로길이
#define HisCntStart 8   //His 몇번째부터
#define HisCntEnd 8		//His 몇번째까지
#define HtcCntStart 1	//Htc 몇번째부터
#define HtcCntEnd 1		//Htc 몇번째까지

Mat Img, ImgClone, ImgClone2;
String Path, PathDir, FileName;
int mx1 = 0, my1 = 0, mx2 = 0, my2 = 0, mx3 = 0, my3 = 0;	// 마우스로 지정한 사각형의 좌표*/
bool Flag = false;
void onMouse(int event, int x, int y, int flags, void* param) // 마우스 콜백 함수
{
	if (event == EVENT_LBUTTONDOWN) {	// 마우스의 왼쪽 버튼을 누르면
		Flag = true;
		mx1 = x;    my1 = y; 		// 사각형의 좌측 상단 좌표 저장
		ImgClone2 = Img.clone();
	}
	/*else if (event == EVENT_MOUSEMOVE) {
		if (Flag == true) {
			mx3 = x; my3 = y;
			if (mx1 <= mx3) {
				rectangle(Img, Rect(mx1, my1, (mx3 - mx1) / 4, my3 - my1), Scalar(0, 255, 0), 1, 4);//value 마다 사각형 표시
				rectangle(Img, Rect(mx1 + ((mx3 - mx1) / 4), my1, (mx3 - mx1) / 4, my3 - my1), Scalar(0, 255, 0), 1,4);
				rectangle(Img, Rect(mx1 + (((mx3 - mx1) * 2) / 4), my1, (mx3 - mx1) / 4, my3 - my1), Scalar(0, 255, 0), 1,4);
				rectangle(Img, Rect(mx1 + (((mx3 - mx1) * 3) / 4), my1, (mx3 - mx1) / 4, my3 - my1), Scalar(0, 255, 0), 1,4);
			}
			else if (mx1 > mx3) {
				rectangle(Img, Rect(mx3, my1, -(mx3 - mx1) / 4, my3 - my1), Scalar(0, 255, 0), 1);//value 마다 사각형 표시
				rectangle(Img, Rect(mx3 - ((mx3 - mx1) / 4), my1, -(mx3 - mx1) / 4, my3 - my1), Scalar(0, 255, 0), 1);
				rectangle(Img, Rect(mx3 - (((mx3 - mx1) * 2) / 4), my1, -(mx3 - mx1) / 4, my3 - my1), Scalar(0, 255, 0), 1);
				rectangle(Img, Rect(mx3 - (((mx3 - mx1) * 3) / 4), my1, -(mx3 - mx1) / 4, my3 - my1), Scalar(0, 255, 0), 1);
			}
			imshow("Default", Img);
		}
	}*/
	else if (event == EVENT_LBUTTONUP) {	// 마우스의 왼쪽 버튼에서 손을 떼면
		if (Flag == true) {
			Flag = false;
			mx2 = x;    my2 = y;       	// 사각형의 우측 하단 좌표 저장
			if (mx1 <= mx2) {
				rectangle(ImgClone2, Rect(mx1, my1, (mx2 - mx1) / 4, my2 - my1), Scalar(0, 255, 0), 1, 8);//value 마다 사각형 표시
				rectangle(ImgClone2, Rect(mx1 + ((mx2 - mx1) / 4), my1, (mx2 - mx1) / 4, my2 - my1), Scalar(0, 255, 0), 1);
				rectangle(ImgClone2, Rect(mx1 + (((mx2 - mx1) * 2) / 4), my1, (mx2 - mx1) / 4, my2 - my1), Scalar(0, 255, 0), 1);
				rectangle(ImgClone2, Rect(mx1 + (((mx2 - mx1) * 3) / 4), my1, (mx2 - mx1) / 4, my2 - my1), Scalar(0, 255, 0), 1);
			}
			else if (mx1 > mx2) {
				rectangle(ImgClone2, Rect(mx2, my1, -(mx2 - mx1) / 4, my2 - my1), Scalar(0, 255, 0), 1);//value 마다 사각형 표시
				rectangle(ImgClone2, Rect(mx2 - ((mx2 - mx1) / 4), my1, -(mx2 - mx1) / 4, my2 - my1), Scalar(0, 255, 0), 1);
				rectangle(ImgClone2, Rect(mx2 - (((mx2 - mx1) * 2) / 4), my1, -(mx2 - mx1) / 4, my2 - my1), Scalar(0, 255, 0), 1);
				rectangle(ImgClone2, Rect(mx2 - (((mx2 - mx1) * 3) / 4), my1, -(mx2 - mx1) / 4, my2 - my1), Scalar(0, 255, 0), 1);
			}

			cout << "mx1 = " << mx1 << " my1 = " << my1 << ", mx2 = " << mx2 << " my2 = " << my2 << endl;
			cout << mx2 - mx1 << " , " << my2 - my1 << endl;
			imshow("WishArea", ImgClone2);
		}
	}
}

void TakeValueNum(int Num) { //표시할 Value의 갯수 함수
	Mat TEST_Graph, TEST_Value;
	int Cnt = 0;
	//그래프 부분 자르고 붙이기
	TEST_Graph = ImgClone(Rect(150, 0, 650 - 150, 408 - 0));
	resize(TEST_Graph, TEST_Graph, Size((Img.cols * 4) / 8, Img.rows));
	Mat TEST_Graph_Sub(Img, Rect(0, 0, TEST_Graph.cols, TEST_Graph.rows));
	TEST_Graph.copyTo(TEST_Graph_Sub);
	//Value 부분 자르고 붙이기
	while (Cnt < Num) {
		if (mx1 <= mx2) {
			TEST_Value = ImgClone(Rect(mx1 + (((mx2 - mx1) * Cnt) / 4), my1, (mx2 - mx1) / 4, my2 - my1));
		}
		else if (mx1 > mx2) {
			TEST_Value = ImgClone(Rect(mx2 - (((mx2 - mx1) * Cnt) / 4), my1, -(mx2 - mx1) / 4, my2 - my1));
		}
		resize(TEST_Value, TEST_Value, Size((Img.cols * 4) / 8, Img.rows / Num));
		Mat TEST_Value_Sub(Img, Rect(TEST_Graph.cols, (Img.rows * Cnt) / Num, TEST_Value.cols, TEST_Value.rows));

		TEST_Value.copyTo(TEST_Value_Sub);
		Cnt++;
	}
	imshow("result4", Img);
	imwrite(String(PathDir + "\\" + FileName + "_ScreenShot_Cut.jpg"), Img);//파일 저장						
}

void MakeDirPath(int FirstDir, int SecondDir) { //편집할 이미지를 읽고 쓰기 위한 주소 변환 함수
	String HisName, HtcName;
	if (FirstDir < 10 && SecondDir < 10) {//디렉토리 이름 바꾸기
		HisName = String("HIS_0" + to_string(FirstDir));
		HtcName = String("HTC_0" + to_string(FirstDir) + "0" + to_string(SecondDir));
	}
	else if (FirstDir < 10) {
		HisName = String("HIS_0" + to_string(FirstDir));
		HtcName = String("HTC_0" + to_string(FirstDir) + to_string(SecondDir));
	}
	else if (SecondDir < 10) {
		HisName = String("HIS_" + to_string(FirstDir));
		HtcName = String("HTC_" + to_string(FirstDir) + "0" + to_string(SecondDir));
	}
	else
		HtcName = String("HTC_" + to_string(FirstDir) + to_string(SecondDir));

	Path = String("C:\\HyunBo_TEST\\" + HisName + "\\" + HtcName + "\\*.jpg");//해당 디렉토리의 .jpg파일을 전부 읽어 Vector<String>배열에 저장
	PathDir = String("C:\\HyunBo_TEST\\" + HisName + "\\" + HtcName);//디렉토리 존재 여부를 위해 주소 저장0
}
void main() {
	vector<String> Str;
	
	//img = imread("C:\\tistory\\tistory.com\\lenna.jpg");
	//정렬
	//glob(Path, Str, false);
	//cout << "해당 폴더의 파일 개수 : " << Str.size() << "\n첫번째 파일 이름 : " << Str[0]<<"\n"<< Path << endl;
	//if (Str.size() == 0) {
	//	cout << "파일이 존재하지 않음\n" << endl;
	//}
	//String HisName = Path.substr(Path.find("\\", Path.find("\\") + 1) + 1, (Path.find("\\", Path.find("\\", Path.find("\\") + 1) + 1) - (Path.find("\\", Path.find("\\") + 1) + 1)));
	//String HtcName = Path.substr(Path.find("\\", Path.find("\\", Path.find("\\") + 1) + 1) + 1, (Path.find("\\", Path.find("\\", Path.find("\\", Path.find("\\") + 1) + 1) + 1) - (Path.find("\\", Path.find("\\", Path.find("\\") + 1) + 1) + 1)));
	//String HisNum = HisName.substr(HisName.length() - 2, 2);
	//String HtcNum = HisName.substr(HtcName.length() - 4, 4);
	//String HisName = String("HIS_0" + to_string(1));
	
	//cout << "HIS 이름 : " << HisName << "\nHTC 이름 : " << HtcName << "\nHIS 번호 : " << HisNum << endl;
	for (int a = HisCntStart; a <= HisCntEnd; a++) {//범위
		for (int b = HtcCntStart; b <= HtcCntEnd; b++) {
			MakeDirPath(a, b);
			//test = String("C:\\HyunBo_TEST\\" + HisName + "\\" + HtcName + "\\*.jpg");
			//cout << Path << endl;
			if (access(PathDir.c_str(), 0) != -1) { //디렉토리 존재여부 판단(-1이면 없는 거)
				glob(Path, Str, false); //Path주소의 이미지 파일 주소 및 이름 저장(만약 디렉토리가 없다면 오류 걸림)
				if (Str.size() > 0) { //해당 디렉토리 파일 개수
					for (int c = 0; c < Str.size(); c++) {
						cout << Str[c] << endl;
						Img = imread(Str[c]); //디렉토리에서 가져온 이미지 파일 읽기
						resize(Img, Img, Size(ImgSizeCows, ImgSizeRows)); //읽어온 이미지 사이즈가 다를 수 있어 (800X547)로 통일
						if (mx1 <= mx2) {
							rectangle(Img, Rect(mx1, my1, (mx2 - mx1) / 4, my2 - my1), Scalar(0, 255, 0), 1, 8);//value 마다 사각형 표시
							rectangle(Img, Rect(mx1 + ((mx2 - mx1) / 4), my1, (mx2 - mx1) / 4, my2 - my1), Scalar(0, 255, 0), 1);
							rectangle(Img, Rect(mx1 + (((mx2 - mx1) * 2) / 4), my1, (mx2 - mx1) / 4, my2 - my1), Scalar(0, 255, 0), 1);
							rectangle(Img, Rect(mx1 + (((mx2 - mx1) * 3) / 4), my1, (mx2 - mx1) / 4, my2 - my1), Scalar(0, 255, 0), 1);
						}
						else if (mx1 > mx2) {
							rectangle(Img, Rect(mx2, my1, -(mx2 - mx1) / 4, my2 - my1), Scalar(0, 255, 0), 1);//value 마다 사각형 표시
							rectangle(Img, Rect(mx2 - ((mx2 - mx1) / 4), my1, -(mx2 - mx1) / 4, my2 - my1), Scalar(0, 255, 0), 1);
							rectangle(Img, Rect(mx2 - (((mx2 - mx1) * 2) / 4), my1, -(mx2 - mx1) / 4, my2 - my1), Scalar(0, 255, 0), 1);
							rectangle(Img, Rect(mx2 - (((mx2 - mx1) * 3) / 4), my1, -(mx2 - mx1) / 4, my2 - my1), Scalar(0, 255, 0), 1);
						}
						imshow("Main_ScreenShot", Img);
						ImgClone = Img.clone();//원본 깊은 복사

						//파일 이름만 저장
						FileName = Str[c].substr(Str[c].find("\\", Str[c].find("\\", Str[c].find("\\", Str[c].find("\\") + 1) + 1) + 1) + 1, Str[c].find(".jpg") - (Str[c].find("\\", Str[c].find("\\", Str[c].find("\\", Str[c].find("\\") + 1) + 1) + 1) + 1));
						cout << Str[c].find("\\", Str[c].find("\\", Str[c].find("\\", Str[c].find("\\") + 1) + 1) + 1) + 1 << "\n" << Str[c].find(".jpg") <<"\n"<< c << endl;

						int key = waitKey(); //Key를 누를 때까지 기다림

						if (key == 'q') break;	// 사용자가 ‘q’를 누르면 종료(저장X)
						
						else if (key == 'w') { //'w'를 누그면 자를 영역을 다시 설정할 수 있다
							destroyWindow("Main_ScreenShot");//"Main_ScreenShot"창 닫기(Key와 마우스 콜백이 겹쳐지지 않기 위해)
							imshow("WishArea", Img);
							cout << "편집할 Value영역을 지정해주세요." << endl;
							setMouseCallback("WishArea", onMouse);
							while (1) {
								if (waitKey() == 'e') {
									cout << "Value영역을 지정 완료하였습니다." << endl;
									destroyWindow("WishArea");//편집할 관심영역이 설정되면 WishArea창 닫기
									c--;
									break;
								}
							}
						}
						/*else if (key == 'c') {	// 사용자가 ‘c’를 누르면 관심영역을 파일로 저장
							//자르기
							TEST_Graph = ImgClone(Rect(150, 0, 650 - 150, 408 - 0));
							TEST_Value1 = ImgClone(Rect(4, 458, 101 - 4, 546 - 458));
							TEST_Value2 = ImgClone(Rect(104, 458, 201 - 104, 546 - 458));
							//사이즈 조절
							resize(TEST_Graph, TEST_Graph, Size((Img.cols * 4) / 8, Img.rows));
							resize(TEST_Value1, TEST_Value1, Size((Img.cols * 4) / 8, Img.rows / 2));
							resize(TEST_Value2, TEST_Value2, Size((Img.cols * 4) / 8, Img.rows / 2));
							//img에 붙여 넣을 공간 생성
							Mat TEST_Graph_Sub(Img, Rect(0, 0, TEST_Graph.cols, TEST_Graph.rows));
							Mat TEST_Value1_Sub(Img, Rect(TEST_Graph.cols, 0, TEST_Value1.cols, TEST_Value1.rows));
							Mat TEST_Value2_Sub(Img, Rect(TEST_Graph.cols, Img.rows / 2, TEST_Value2.cols, TEST_Value2.rows));
							//자른 부분 붙여넣기
							TEST_Graph.copyTo(TEST_Graph_Sub);
							TEST_Value1.copyTo(TEST_Value1_Sub);
							TEST_Value2.copyTo(TEST_Value2_Sub);
							//결과 보여주기
							imshow("result4", Img);
						}*/
						else if (key == 'v') {	// 사용자가 ‘v’를 누르면 관심영역을 파일로 저장
							TakeValueNum(2);
						}
						else if (key == 'b') {	// 사용자가 ‘b’를 누르면 관심영역을 파일로 저장
							TakeValueNum(3);
						}
						else if (key == 'n') {	// 사용자가 ‘n’를 누르면 관심영역을 파일로 저장
							TakeValueNum(4);
						}						
					}
					//Str.clear();
				}
			}
		}
	}
}
