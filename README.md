# Refrigerator_ComputerGraphics
### 2020-2학기 컴퓨터그래픽스설계 프로젝트
Blender, OpenGL을 이용하여 양문형 냉장고 카탈로그를 구현하였습니다.
<br>

### Details
![그림2](https://user-images.githubusercontent.com/63782957/176839937-3569624b-61db-4225-86fb-cb7331345c5c.png)
<br>
<li>내부 저장고 8칸</li>
<li>양쪽 문 내부 2칸</li>
<li>오른쪽 문 외부 홈바</li>
<br>

### Functions

|Key|Event|
|------|---|
|방향키|시점 이동|
|mouse wheel|Zoom in/out|
|keyboard '1','2'|left,right door open/close|
|keyboard '3'|Homebar open/close|
|**right mouse button**|**냉장고 텍스처/색 변경**|
||**Keep/Take out food**|
|keyboard 'q'|분해/재조립|
|keyboard 'z'|조작법 on/off|
|keyboard 'a'|조명 on/off|
|*mouse button*|*픽업된 음료 보관(2차 개선)*|
<br>

### Textures

<img width="236" alt="스크린샷 2022-07-01 오후 3 50 59" src="https://user-images.githubusercontent.com/63782957/176840220-24719c73-5d22-4881-aea5-240ad41854bf.png">
<br>
<li>오른쪽 마우스 - Style 에서 변경</li>

### Menu

![그림1](https://user-images.githubusercontent.com/63782957/176840735-d23a3f2d-1a14-469f-b477-5881f7bc7505.png)
<li>Init view : 시점 초기화</li>
<li>Store food : 콜라/사이다 저장</li>
<li>Pick up : 콜라/사이다 손에 들기</li><br>

![그림2](https://user-images.githubusercontent.com/63782957/176840799-0e484363-8575-473f-9cc1-b5c315fa18b0.png)

음료를 픽업한 상태에서 마우스로 음료 클릭 시, 음료가 다시 냉장고에 보관됩니다.

### Alert
문을 열어두고 일정 시간이 지나면 경고음, 경고메시지가 출력됩니다.
<li>"mmsystem.h"의 PlaySound 함수 이용</li>

### Tools
<img src="https://img.shields.io/badge/OpenGL-5586A4?style=flat-square&logo=OpenGL&logoColor=white"/></a>&nbsp;
<img src="https://img.shields.io/badge/C++-00599C?style=flat-square&logo=C%2B%2B&logoColor=white"/></a>&nbsp;
<img src="https://img.shields.io/badge/Blender-F5792A?style=flat-square&logo=Blender&logoColor=white"/></a>&nbsp;
### Video
https://youtu.be/LtIVhGYorh4 <br>
<br>
### Reference
Model : https://free3d.com/ko/3d-model/refrigerator-v1--613633.html<br><br>
Texture images : <br>
https://pxhere.com/ko/photo/546299 <br> https://me6me6.tistory.com/19 <br> https://m.blog.naver.com/PostView.nhn?blogId=08823&logNo=176742692&proxyReferer=https%3A%2F%2Fwww.google.com%2F
<br><br>
Sound : https://kimchimandoo.tistory.com/41
<br>
