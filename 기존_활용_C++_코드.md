# 기존 프로젝트 → 새 프로젝트 이전 가이드

---

## 1. 새 프로젝트 세팅 순서

```
1. 새 프로젝트 생성 (Third Person 템플릿, C++)

2. ALS 플러그인 먼저 설치
   └─ HiCharacter가 AAlsCharacterExample 상속
      ALS 없으면 컴파일 자체가 안 됨

3. C++ 파일 복사 (아래 목록 참고)

4. Build.cs 교체 (아래 내용 참고)

5. prototypeTags.h/.cpp에서 Hiking 관련 태그 정리
   └─ Tag_Hiking_Item_*, Tag_Hiking_Character_Anim_Dance_Twist 제거
   └─ 새 게임용 태그 추가 (아래 태그 목록 참고)

6. 블루프린트 에셋 마이그레이션
   └─ 콘텐츠 브라우저 우클릭 → 에셋 마이그레이션

7. BB_Hiking_NPC에 Blackboard 키 6개 추가 (핵심기능.md 참고)

8. BT_SocialNPC 새로 제작 (기존 BT는 배회용으로 재활용)
```

---

## 2. Build.cs — 새 프로젝트용

> 파일 위치: `Source/[프로젝트명]/[프로젝트명].Build.cs`
> 기존 Build.cs에서 불필요한 Variant 경로 제거, GameplayTasks 추가

```csharp
using UnrealBuildTool;

public class [프로젝트명] : ModuleRules
{
    public [프로젝트명](ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "EnhancedInput",
            "AIModule",
            "GameplayTasks",        // BehaviorTree Task용
            "NavigationSystem",     // MoveTo, NavMesh용
            "GameplayTags",         // NPC 타입 태그용
            "StateTreeModule",
            "GameplayStateTreeModule",
            "UMG",
            "Slate",
            "ALS",
            "ALSExtras",
            "DeveloperSettings",
        });

        PrivateDependencyModuleNames.AddRange(new string[] { });

        PublicIncludePaths.AddRange(new string[]
        {
            "[프로젝트명]",
        });
    }
}
```

---

## 3. 가져갈 C++ 파일 목록

### ✅ 반드시 가져갈 것

**NPC AI 핵심**
```
Characters/AI/HiAICharacter.h
Characters/AI/HiAICharacter.cpp     ← PawnSensing 추가 필요 (아래 참고)
Characters/AI/HiAIController.h
Characters/AI/HiAIController.cpp
Characters/AI/HiAISpawner.h
Characters/AI/HiAISpawner.cpp
Data/HiAICharacterData.h
Data/HiAICharacterData.cpp
```

**플레이어 캐릭터**
```
Characters/HiCharacter.h
Characters/HiCharacter.cpp
Characters/HiPlayerController.h
Characters/HiPlayerController.cpp
```

**멘탈 체력**
```
Private/PlayerStatComponent.h       → Public/PlayerStatComponent.h 로 이동
Private/PlayerStatComponent.cpp
Private/StatEffectMessage.h         → Public/StatEffectMessage.h 로 이동
Private/StatEffectMessage.cpp
```

**인터랙션 (체크리스트용)**
```
Interaction/HiInteractionComponent.h
Interaction/HiInteractionComponent.cpp
Interaction/HiPickupBase.h
Interaction/HiPickupBase.cpp
```

**그룹 NPC (시장 거리용)**
```
Public/EncounterActor.h
Private/EncounterActor.cpp
Public/HikerGroupActor.h
Private/HikerGroupActor.cpp
```

**태그**
```
prototypeTags.h
prototypeTags.cpp
```

---

### ⚠️ 조건부 (나중에 판단)
```
Private/UIController.h/.cpp              ← UI 관리 구조 참고용
Private/UIControllerBootstrapSubsystem   ← 같은 이유
Private/PlayerStatWidget.h/.cpp          ← 멘탈 게이지 UI 만들 때 참고
Private/MinigameCameraComponent.h/.cpp   ← 카메라 연출 참고용
```

---

### ❌ 버릴 것
```
Private/InventoryComponent          상점 시스템
Private/InventoryWidget             상점 UI
Private/InventoryTileWidget         상점 UI
Private/QuickSlotComponent          장비 퀵슬롯
Private/QuickSlotsWidget            퀵슬롯 UI
Private/RhythmHUDWidgetBase         리듬 미니게임
Private/RhythmMinigameManagerBase   리듬 미니게임
Private/RhythmNoteWidgetBase        리듬 미니게임
Private/HealEffect                  회복 아이템
Private/WaterEffect                 물 효과
Private/HikingWorldSettings         하이킹 맵 전용
Characters/Components/HiGearManagerComponent  장비 관리
Public/ItemData                     아이템 시스템
Public/ItemEffect                   아이템 시스템
Public/ItemStack                    아이템 시스템
Data/HiAnimData                     하이킹 전용 애니 데이터
Data/HiStickMovementAnimData        지팡이 입력 전용
```

---

## 4. 마이그레이션할 블루프린트/에셋 목록

```
BB_Hiking_NPC           Blackboard  키 6개 추가 후 마이그레이션
BT_AI_Default           BehaviorTree  NPC 배회용 (BT_SocialNPC 5순위로 재활용)
BT_AI_Default_Walk      BehaviorTree  걷기 배회용
HiAICharacterData 에셋  DataAsset   NPC 데이터 (BT/메시/태그 묶음)
EQS_SmartObj            EQS         NPC 위치 쿼리 (없으면 BT 에러)
```

> BT_SocialNPC는 새 프로젝트에서 직접 제작

---

## 5. HiAICharacter.h — PawnSensing 추가 버전

> 기존 파일에서 아래 내용 추가

```cpp
// HiAICharacter.h 에 추가할 내용

#include "Perception/PawnSensingComponent.h"

// 클래스 내부 protected: 에 추가
protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AI|Sensing")
    TObjectPtr<UPawnSensingComponent> PawnSensingComp = nullptr;

    UFUNCTION()
    void OnSeePawn(APawn* SeenPawn);
```

```cpp
// HiAICharacter.cpp 에 추가할 내용

// 생성자에 추가
PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing"));
PawnSensingComp->SightRadius = 500.f;
PawnSensingComp->SetPeripheralVisionAngle(60.f);

// BeginPlay에 추가
PawnSensingComp->OnSeePawn.AddDynamic(this, &AHiAICharacter::OnSeePawn);

// 함수 구현 추가
void AHiAICharacter::OnSeePawn(APawn* SeenPawn)
{
    if (!SeenPawn || !SeenPawn->IsPlayerControlled()) return;

    // 플레이어의 ReactionComponent에 이벤트 전달
    if (auto* RC = SeenPawn->FindComponentByClass<USocialAnxietyReactionComponent>())
    {
        const float Dist = FVector::Dist(GetActorLocation(), SeenPawn->GetActorLocation());
        RC->OnNPCSeen(this, Dist);
    }

    // Blackboard에 PlayerPawn 세팅
    if (auto* BB = UAIBlueprintHelperLibrary::GetBlackboard(this))
    {
        BB->SetValueAsObject(FName("PlayerPawn"), SeenPawn);
    }
}
```

---

## 6. prototypeTags — 새 게임용 태그 추가

> prototypeTags.h 에서 Hiking 태그 제거 후 아래 추가

```cpp
// 사회불안 게임 전용 태그

// NPC 타입
PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_SocialNPC_Passerby);    // 행인
PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_SocialNPC_Auntie);      // 말거는 아주머니
PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_SocialNPC_Blocker);     // 통로 막는 NPC
PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_SocialNPC_Group);       // 단체 그룹

// NPC 상태
PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_SocialNPC_State_Idle);
PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_SocialNPC_State_Watching);
PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_SocialNPC_State_Fleeing);
PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_SocialNPC_State_Talking);

// 플레이어 상태
PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Player_State_Crouching);
PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Player_State_Fainted);
PROTOTYPE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_Player_State_Breathless);
```
