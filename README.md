# :pushpin:Picture_Editer
## 1. 목적
> LrCroy Corporation사의 **oscilloscope screenshot**을 편집하기 위한 **OpenCV_4.1.1**로 제작된 이미지 **일괄 자르기 APP**
<br/>

## 2. 제작기간 & 참여인원
- 2022년 02월 16일 ~ 02월 22일
- 개인 프로젝트
<br/>

## 3. stack
### 사용 언어 & 프로그램

- <img src="https://img.shields.io/badge/C++-00599C?style=flat-square&logo=C%2B%2B&logoColor=white"/>
- <img src="https://img.shields.io/badge/OpenCV-5C3EE8?style=flat-square&logo=Opencv"/>
- <img src="https://img.shields.io/badge/Visual Studio-5C2D91?style=flat-square&logo=Visual Studio&logoColor=white"/></a> 

## 4. 핵심기능

- 이 프로그램의 **핵심 기능은 oscilloscope의 measure value값들이 포함된 screenshot을 measure value값개수에 따라 사진을 편집할 수 있는 기능**입니다.<br/>
- LrCroy Corporation사의 **oscilloscope 인터페이스**는 measure value값 폰트를 확대하는 기능이 없어 제작하게된 이미지 편집 Application입니다.<br/>
- 원하는 directory내의 image file을 읽어 screenshot의 measure value값이 있는 영역을 확대하여 그래프와 함게 보이도록 새로 편집됩니다.<br/>
- 이를 통해 문서정리를 통해 H/W Test 증거자료로 담아낼 때 한 페이지에 여러개 붙여도 **oscilloscope의 measure value값이** 잘보인다는 장점이 있습니다.<br/>

<details>
<summary> :mag_right: 핵심 기능 설명 펼치기 </summary>
<div markdown="1">  

### 4.1 ISO26262 Hardware Intergration Test
차량 전장 부품의 안전 기능의 완전성과 정확성을 목적으로 ISO26262(기능 안전 표준)에서 Hardware Intergration Test를 요구합니다.
Hardware Intergration Step(HIS)를 큰 틀로 구분하고 Hardware Test Component(HTC)를 세부적인 틀로 Test 조건을 정해 회로실험 장비로 Test를 진행합니다.
HIS와 HTC를 정렬하여 directory를 만들고 HTC폴더마다 oscilloscope screenshot으로 실제 Test결과 증거로 남겨둡니다.

### 4.2 directory 처리
정렬된 directory의 이름을 읽어 directory 내의 image file을 읽기 위해 **glob()**함수를 사용합니다.
**glob()**함수를 사용하기 위해서는 directory주소를 문자열로 기입시켜야 함으로 문자열 처리를 위해 **MakeDirPath()**함수를 만들어 주었습니다.
문자열 처리를 하여 **cv::glob()**로 해당 directory내의 image file을 전부 차례대로 불러옵니다.
편집이 종료된 편집본 image file은 문자열을 추가하여 해당 directory 내에 편집본을 저장시킵니다.

### 4.3 MouseCallback
관심영역을 선택하여 편집을 해야하기 때문에 **cv::setMouseCallback()**함수를 사용하여 관심영역을 그립니다.
몇개의 measure value를 편집하느냐에 따라 관심영역 내 사각형이 몇개 그려질지 결정됩니다.

### 4.4 image edit
불러온 directory 내의 screenshot image를 작을 화소로도 잘 보이도록 measure value값과 그래프가 편집을 시킵니다.
2~6개의 measure value개수를 조절하여 image를 편집합니다.

</div>
</details>
<br/>

## 5. 핵심 트러블 슈팅
### 5.1 glob()함수 오류 방지
- directory에서 image file이 존재하지 않을 경우 **cv::glob()**함수는 오류 발생 동시에 프로그램을 끝내버립니다.
  
<details>
<summary style="font-Weight : bold; font-size : 15px; color : #E43914;"> :confused: 기존 코드</summary>
<div markdown="1">  

```c++
    glob(Path, Str, false); //Path주소의 이미지 파일 주소 및 이름 저장(만약 디렉토리가 없다면 오류 걸림)
    if (Str.size() > 0) { //해당 디렉토리의 image 파일 존재유무
        for (int c = 0; c < Str.size(); c++) {
            cout << Str[c] << endl;
            Img = imread(Str[c]); //디렉토리에서 가져온 이미지 파일 읽기
            ...
            //image file 편집 알고리즘
            ...
        }
    }
```
</div>
</details>
<br/>

- 이를 방지하기 위해 [access()함수](https://bubble-dev.tistory.com/entry/CC-access2)로 해당 directory내 파일 유무 검사하여 **cv::glob()**함수의 오류발생을 예방합니다.
  
  <details>
   <summary style="font-Weight : bold; font-size : 15px; color : #E43914;"> :smile: 개선된 코드 </summary>
   <div markdown="1">  


   ```c++
   if (access(PathDir.c_str(), 0) != -1) { //디렉토리 존재여부 판단(-1이면 없는 거)
        glob(Path, Str, false); //Path주소의 이미지 파일 주소 및 이름 저장(만약 디렉토리가 없다면 오류 걸림)
        if (Str.size() > 0) { //해당 디렉토리의 image 파일 존재유무
            for (int c = 0; c < Str.size(); c++) {
                cout << Str[c] << endl;
                Img = imread(Str[c]); //디렉토리에서 가져온 이미지 파일 읽기
                ...
                //image file 편집 알고리즘
                ...
            }
        }
   }
   
   ```
   </div>
   </details>
<br/>


## 6. 그 외 트러블 슈팅
