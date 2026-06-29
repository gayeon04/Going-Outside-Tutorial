# CLAUDE.md

Follow all rules in `AGENTS.md`.

## Claude Code Specific Reminders

* Prefer small, reviewable changes.
* Do not only edit code — for every meaningful change, update the relevant documentation in `Docs/`.
* If documentation was not updated, explain why in the final response.
* If a change may break Blueprint references, explain the risk before making the change.
* Do not rename `UCLASS`, `USTRUCT`, `UENUM`, `UPROPERTY`, or `UFUNCTION` unless explicitly requested.
* Do not move or rename assets in `Content/` unless explicitly requested.
* Be extra careful with: Blueprint-exposed names, widget flow, GameInstance initialization, input mode, and packaged-build behavior.

## Final Response Format

At the end of every task, always include:

1. What code changed
2. What documentation changed
3. What should be checked manually in Unreal Editor
4. Any Blueprint or packaging risks
