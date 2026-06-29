# FeatureLog.md

기능 추가, 변경, 버그 수정 이력을 기록한다.
의미 있는 작업이 완료될 때마다 아래 형식으로 항목을 추가한다.

---

## Template

```md
## YYYY-MM-DD - Feature or Fix Name

### Summary
무엇을 추가/변경/수정했는지 간략히 설명한다.
완성 여부도 명시한다. (예: 완성 / 미완성 — 쿨타임 로직 미구현)

### Changed Files
- `Source/...`
- `Config/...`
- `Content/...` (해당하는 경우)

### Unreal / Blueprint Impact
이 변경이 Blueprint 참조, 위젯, 레벨 액터, 입력 매핑, DataAsset, 에디터 설정에
영향을 주는지 설명한다.
영향이 없는 경우에도 왜 없는지 한 줄 이상 설명한다.

### Reason
왜 이 변경을 했는지 설명한다.

### Manual Test Checklist
- [ ] Unreal Editor에서 확인
- [ ] Blueprint 참조 확인
- [ ] 패키징 빌드 확인 (해당하는 경우)

### Notes for Future Agents
미래의 AI 에이전트가 알아야 할 경고, 가정, 취약한 부분을 기술한다.
미완성 상태나 임시 구현도 여기에 명시한다.
```

---

<!-- 아래에 실제 항목을 추가한다. 최신 항목이 위에 오도록 한다. -->
