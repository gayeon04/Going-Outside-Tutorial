# Architecture.md

## Overview

사회불안 히키코모리 캐릭터가 전통시장을 통과해 엄마에게 선물을 전달하는 게임.
핵심 재미: NPC 시선/접근 → 플레이어 리액션의 타이밍 개그.
C++ 로직 + Blueprint 연출 + BehaviorTree NPC 행동의 3-레이어 구조.

## Core Systems

| Class | Type | Responsibility |
|-------|------|----------------|
| `USocialAnxietyReactionComponent` | ActorComponent | 트리거 수신 → 강도 계산 → 이벤트 브로드캐스트 |
| `UPlayerStatComponent` | ActorComponent | 멘탈 수치 관리 |
| `AHiCharacter` | Character (ALS) | 플레이어. ReactionComponent + StatComponent 소유 |
| `AHiAICharacter` | Character | NPC. PawnSensing으로 감지 후 ReactionComponent 호출 |
| `AHiAIController` | AIController | BehaviorTree 실행, Blackboard 관리 |
| `AHiAISpawner` | Actor | 맵별 NPC 스폰 |
| `AHikerGroupActor` | Actor | 단체 그룹 NPC (기존 코드 재활용) |
| `UHiInteractionComponent` | ActorComponent | 체크리스트 아이템 인터랙션 |

## Initialization Order

1. `UPlayerStatComponent` BeginPlay — 멘탈 수치 초기화
2. `USocialAnxietyReactionComponent` BeginPlay — StatComponent 참조 연결
3. `AHiAICharacter` BeginPlay — PawnSensing 델리게이트 바인딩
4. Blueprint (`BP_HiCharacter`) — OnReactionTriggered / OnIntensityChanged 바인딩

> ⚠️ ReactionComponent는 반드시 StatComponent 이후에 초기화되어야 한다.

## UI Flow

<!-- 구현 시작 후 채운다 -->

## Level Transition Flow

레벨 스트리밍 방식. 서브레벨 구성:

```
L_Persistent   항상 로드 — GameMode, PlayerController, UI
L_Hallway      복도 + 엘리베이터
L_Street       건물 밖 거리
L_Market       전통시장 골목
```

멘탈 수치와 체크리스트 상태는 레벨 전환 후에도 유지된다.
NPC Blackboard 상태는 서브레벨 언로드 시 초기화된다.

## Data Ownership

| 데이터 | 소유 클래스 |
|--------|------------|
| 멘탈 수치 | `UPlayerStatComponent` (Persistent Level 소속) |
| 체크리스트 상태 | `GameInstance` |
| NPC 행동 상태 | `Blackboard` (NPC 언로드 시 소멸) |

## Input Mode

<!-- 구현 시작 후 채운다 -->

## Change Log

| Date | Change | Reason |
|------|--------|--------|
| 2025-06-17 | 초안 작성 | 프로젝트 시작 |
