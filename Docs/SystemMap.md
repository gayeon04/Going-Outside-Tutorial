# SystemMap.md

High-level Mermaid diagrams of the project flow and ownership.

Keep diagrams high-level. Do not include every class, function, or Blueprint node.
Update this file when high-level flow, ownership, or initialization order changes.

---

## Overall System Flow

```mermaid
flowchart TD
    NPC[AHiAICharacter\nPawnSensing] -->|OnSeePawn| RC[USocialAnxietyReactionComponent]
    RC -->|참조| STAT[UPlayerStatComponent]
    RC -->|ApplyDamagePoints| STAT
    RC -->|OnReactionTriggered| BP[BP_HiCharacter\n블루프린트 연출]
    RC -->|NotifyNearbyNPCs| BB[Blackboard]
    BB --> BT[BT_SocialNPC]
    STAT -->|OnPlayerDead| GO[수치사 게임오버]
```

---

## UI Flow

```mermaid
flowchart TD
    A[...] --> B[...]
```

<!-- 구현 시작 후 채운다 -->

---

## Level Transition Flow

```mermaid
flowchart TD
    TR[트리거 박스 진입] --> FO[페이드 아웃]
    FO --> UL[서브레벨 Unload]
    UL --> LD[다음 서브레벨 Load]
    LD --> FI[페이드 인]
```

---

## Change Log

| Date | Diagram Updated | Reason |
|------|-----------------|--------|
| 2025-06-17 | Overall Flow, Level Transition | 프로젝트 시작 |
