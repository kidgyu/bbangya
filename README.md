[개인프로젝트3]

5살 아이가 할 수 있는 간단한 총 게임 개발
설명
- 화면을 터치 후 좌우로 스크롤 하며 발사되는 총의 방향을 바꾸며 다가오는 적을 없애는 게임
- 레벨이 진행될 수록 생성되는 적이 많아지고 발사되는 총알의 개수 증가

코드 내용
- 적이 많이 생성되므로 Object Pool을 사용하여 미리 대량으로 생성 후 Spawn을 할 때 Pool에서 가져오는 형식으로 제작
- 타입에 따라 다양하게 생성하기 위해 Active/InActive 리스트를 담는 구조체를 만들고, Map으로 타입과 구조체를 관리
- PlayerController를 만들고, 화면 터치/최대 회전 제한 등을 적용
- 적은 부채꼴로 생성하기 위해 GameState에서 플레이어의 위치를 기준으로 랜덤으로 부채꼴 형태 위치를 만들어 적 생성
- 게임 난이도 처리를 하기 위해 UDeveloperSettings를 상속 받아 GameLevelSettings 클래스 구현
- 사운드 세팅도 UDeveloperSettings를 상속 받아 enum과 리소스를 대응시켜 SoundManager에서 enum으로 플레이를 하도록 구성
- WidgetManager를 만들고 UWorldSubsystem를 상속 받아 외부에서 Subsystem을 통해 접근하기 쉽게 구현
- ActorManager, SoundManager, WidgetManager 등도 똑같이 구현
- 나이아가라를 활용하여 이펙트 처리, 액터를 만들고 NiagaraComponent를 추가하는 구조로 만들어 이펙트도 ActorManager에서 관리하도록 처리
-

<img width="952" height="540" alt="2026-08-14-16-57-16" src="https://github.com/user-attachments/assets/57377d6f-e6b7-421d-a8fd-1aad08b5259e" />
