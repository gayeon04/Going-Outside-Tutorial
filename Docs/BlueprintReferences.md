# BlueprintReferences.md

C++ 클래스와 Blueprint 간의 연결 관계를 기록한다.
UCLASS, USTRUCT, UENUM, UPROPERTY, UFUNCTION 변경 시 이 파일을 업데이트한다.

---

## USocialAnxietyReactionComponent

### Blueprints Using This Class
- `BP_HiCharacter`

### Exposed UFUNCTIONs
| Function | Used In | Rename Risk |
|----------|---------|-------------|
| `OnNPCSeen(NPC, Distance)` | BP_HiAICharacter | High |
| `OnNPCLostSight(NPC)` | BP_HiAICharacter | High |
| `OnNPCCollision(NPC)` | BP_HiCharacter | Medium |
| `OnNPCTalking(NPC)` | BP_HiAICharacter | Medium |
| `OnEnvironmentTrigger(Trigger)` | 레벨 트리거 박스 | Medium |
| `NotifyNearbyNPCs(ReactionType)` | BP_HiCharacter | High |

### Exposed UPROPERTYs
| Property | Used In | Rename Risk |
|----------|---------|-------------|
| `OnReactionTriggered` | BP_HiCharacter | High |
| `OnIntensityChanged` | BP_HiCharacter | High |

### Notes
- `OnReactionTriggered`의 `FReactionPayload.Intensity`로 블루프린트에서 연출 분기

---

## UPlayerStatComponent

### Blueprints Using This Class
- `BP_HiCharacter`

### Exposed UPROPERTYs
| Property | Used In | Rename Risk |
|----------|---------|-------------|
| `Health01` | WBP_MentalGauge, ReactionComponent | High |
| `OnPlayerDead` | BP_HiCharacter | High |

### Notes
- `HealthDecayPerSec` = 0 고정. 감소는 ReactionComponent가 전담
- `Health01`은 0~1 범위 float

---

<!-- 아래에 실제 클래스 항목을 추가한다 -->
