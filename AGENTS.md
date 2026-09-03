\# Project Rules



Engine:

\- Unreal Engine 5.4



Language:

\- C++17



Rules:

\- Follow Unreal Engine naming conventions.

\- Prefer TObjectPtr for UObject references where appropriate.

\- Do not modify generated files.

\- Do not edit Engine source.

\- Preserve Blueprint-facing APIs unless explicitly requested.

\- Avoid unnecessary Tick usage.

\- Prefer components over adding responsibilities to Character.



Build:

\- Development Editor / Win64



Architecture:

\- Character handles input and orchestration.

\- Combat logic belongs in CombatComponent.

\- Inventory logic belongs in InventoryComponent.

