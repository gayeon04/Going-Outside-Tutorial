# AGENTS.md

## Project Overview

This is an Unreal Engine project using both C++ and Blueprint.

The project uses a hybrid workflow:

* C++ for reusable core systems, managers, components, data flow, and gameplay logic.
* Blueprint for visual setup, level-specific behavior, widget animation, editor placement, and designer-facing tuning.

Do not rewrite the architecture unless explicitly requested.

## Required Reading Before Work

Before modifying code, read the relevant documents in `Docs/`.

Always check these first when the task may affect structure, UI, Blueprint, or runtime flow:

* `Docs/Architecture.md`
* `Docs/SystemMap.md`
* `Docs/BlueprintReferences.md`
* `Docs/KnownIssues.md`

For small isolated code changes, read only the relevant files and documentation.

## Important Unreal Rules

Do not modify generated or temporary folders:

* `Binaries/`
* `Intermediate/`
* `Saved/`
* `DerivedDataCache/`

Do not manually edit:

* `*.generated.h`
* generated Visual Studio / Rider project files

Be careful with Unreal reflection:

* Do not rename `UCLASS`, `USTRUCT`, `UENUM`, `UPROPERTY`, or `UFUNCTION` casually.
* Blueprint nodes may break if reflected names, signatures, or property types change.
* Prefer adding backward-compatible functions over deleting or renaming Blueprint-exposed APIs.
* Do not move or rename assets in `Content/` unless explicitly requested.
* Do not assume Blueprint references are safe after C++ changes.

## Coding Style

Use Unreal C++ style.

Prefer:

* clear names over short names
* `UPROPERTY` for UObject references that must survive garbage collection
* `TObjectPtr<>` for UObject references when appropriate
* `TWeakObjectPtr<>` for non-owning references
* delegates or interfaces for UI communication
* null checks before accessing UObject references
* `UE_LOG` for debugging important runtime failures

Avoid:

* hard-coded asset paths unless necessary
* creating widgets in too many different places
* storing raw UObject pointers without considering lifetime
* broad refactoring without user approval

## Architecture Preferences

Keep responsibilities separated:

* Manager / Controller classes control flow.
* Widgets display state and handle user interaction.
* Components contain reusable behavior.
* GameInstance stores long-lived run data, not moment-to-moment widget logic.
* Blueprints should handle placement, animation, tuning, and visual setup.

Prefer data-driven design using:

* DataAssets
* DataTables
* configurable Blueprint variables

## UI Rules

Be careful with:

* `AddToViewport`
* `RemoveFromParent`
* widget reuse
* ZOrder
* input mode changes
* cursor visibility
* level transition timing

Avoid repeatedly creating the same persistent widget.

When changing UI flow, explain:

* which class owns the widget
* when the widget is created
* when it is removed or hidden
* what input mode is expected
* whether Blueprint widgets must be checked manually

## Common Risk Areas

Be extra careful with:

* GameInstance initialization
* Subsystems
* UI creation during level transition
* async loading
* Blueprint-exposed C++ changes
* widget references
* input mode switching
* packaged-build-only crashes
* object lifetime and garbage collection
* timer and delegate cleanup
* save/load flow
* level transition flow

## Documentation Rule

For every meaningful task, update project documentation together with code changes.

A meaningful task includes:

* adding a new feature
* changing gameplay logic
* changing UI flow
* modifying C++ and Blueprint interaction
* fixing a bug
* changing project architecture
* changing initialization flow
* changing level transition flow
* changing widget creation or removal flow
* changing input mode behavior
* changing save/load flow
* changing any `UCLASS`, `USTRUCT`, `UENUM`, `UPROPERTY`, or `UFUNCTION`

## NOT Meaningful Tasks

Documentation update is usually not required for:

* typo fixes
* comment-only changes
* log message changes
* formatting-only changes
* local variable rename that is not exposed to Blueprint
* small internal cleanup with no behavior change

However, if the change may affect Unreal Editor setup, Blueprint references, packaging, save data, input, UI flow, or level transition, it must be documented even if the code change is small.

## Anti-Formal Documentation Rule

Do not write empty or meaningless documentation entries.

Avoid:

* `Blueprint Impact: None`
* `Notes: None`
* `Manual Test: Not needed`
* `No impact`

If there is no Blueprint impact, explain why.

Good example:

```md
### Unreal / Blueprint Impact

No Blueprint impact. This change only modifies internal C++ logic inside `UpdateHealthBar()`.
The `UFUNCTION` name, parameters, return type, and exposed `UPROPERTY` fields were not changed,
so existing Blueprint nodes should remain valid.
```

Bad example:

```md
### Unreal / Blueprint Impact

None.
```

## Documentation Targets

Update the appropriate document after meaningful work:

* `Docs/FeatureLog.md` — feature changes, bug fixes, implementation history
* `Docs/Architecture.md` — system responsibility, initialization order, ownership, data flow, UI flow
* `Docs/SystemMap.md` — high-level project flow or ownership (update Mermaid diagram)
* `Docs/BlueprintReferences.md` — C++ and Blueprint interaction changes
* `Docs/KnownIssues.md` — bugs, fragile behavior, packaging issues, Unreal-specific risks
* `Docs/ManualTestChecklist.md` — features requiring Unreal Editor or packaged-build testing

## SystemMap Rule

`Docs/SystemMap.md` contains high-level Mermaid diagrams of the project.

Before changing architecture, UI flow, initialization order, level transition, or data ownership, read `Docs/SystemMap.md`.

After changing any high-level flow or ownership, update `Docs/SystemMap.md`.

Do not update `SystemMap.md` for small internal code changes unless the visible project flow changes.

Keep diagrams high-level. Do not include every class, function, variable, or Blueprint node.

## Blueprint Documentation Rule

If a change affects any `UCLASS`, `USTRUCT`, `UENUM`, `UPROPERTY`, or `UFUNCTION` exposed to Blueprint, update `Docs/BlueprintReferences.md`.

Include:

* which Blueprint may be using it
* whether renaming it may break nodes
* what should be checked in Unreal Editor
* why the change is safe or risky

## Known Issues Rule

If a bug was fixed or a risky Unreal behavior was discovered, update `Docs/KnownIssues.md`.

Include:

* symptom
* cause
* fix
* how to avoid breaking it again
* whether it may appear only in packaged builds

## Workflow Instructions for Agents

When given a task:

1. Read relevant files first.
2. Read relevant documentation in `Docs/`.
3. Summarize the current structure briefly.
4. Propose a small change plan.
5. Make the minimum necessary code changes.
6. Update relevant documentation.
7. Explain what changed and why.
8. List manual Unreal Editor checks if automatic testing is not possible.

Do not make broad refactors unless explicitly requested.

## Documentation Decision Table

Use this table after every task.

| Change Type | Required Docs |
|---|---|
| New feature or gameplay logic change | `Docs/FeatureLog.md` |
| Bug fix | `Docs/FeatureLog.md`, and `Docs/KnownIssues.md` if the bug is risky or may recur |
| UI flow, widget ownership, input mode change | `Docs/FeatureLog.md`, `Docs/Architecture.md`, `Docs/ManualTestChecklist.md` |
| Level transition or initialization order change | `Docs/Architecture.md`, `Docs/SystemMap.md`, `Docs/KnownIssues.md` if risky |
| Blueprint-exposed C++ API change | `Docs/BlueprintReferences.md`, `Docs/ManualTestChecklist.md` |
| High-level ownership or system flow change | `Docs/Architecture.md`, `Docs/SystemMap.md` |
| Editor-only or packaged-build-only issue | `Docs/KnownIssues.md`, `Docs/ManualTestChecklist.md` |
| Comment, formatting, log-only change | Usually no documentation update required |

## Final Response Requirement

At the end of every task, report:

1. What code changed
2. What documentation changed
3. What needs to be checked manually in Unreal Editor
4. Any Blueprint or packaging risks

If documentation was not updated, explain why.

## Git Instructions

* Do not commit automatically unless asked.
* Do not delete files unless asked.
* Do not modify unrelated files.
* Keep changes small and reviewable.
