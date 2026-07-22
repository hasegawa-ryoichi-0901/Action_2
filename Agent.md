# AGENTS.md

# Purpose

This document defines the project-specific review knowledge and review standards
used by Codex when reviewing pull requests in this repository.

Its primary purpose is to improve the consistency, quality, and usefulness of
code reviews for this project.

Unless explicitly requested, these guidelines should be interpreted as review
criteria rather than mandatory implementation requirements.

Implementation suggestions should respect the existing project architecture,
coding conventions, and documented requirements.

---

# Review Philosophy

Prioritize practical, maintainable, and production-quality feedback.

Avoid recommending architectural changes, new frameworks, or design patterns
unless they solve a concrete problem in the current code.

Clearly distinguish between:

- Confirmed defects
- Potential runtime risks
- Design risks
- Optional improvements

Avoid reporting purely theoretical concerns unless realistic failure conditions
are explained.

---

# Project Overview

This repository contains an Unreal Engine 5 C++ action game project.

The project aims to demonstrate:

- Unreal Engine gameplay programming
- C++ architecture and design
- Maintainable gameplay systems
- Portfolio-quality implementation
- Appropriate separation between Blueprint and C++

Blueprint is primarily intended for:

- Asset assignment
- Visual configuration
- Animation setup
- Designer-facing parameters
- Rapid iteration

Core gameplay systems should generally remain in C++.

---

# Language

Write all review summaries and explanations in Japanese.

Code identifiers, Unreal Engine API names, and technical terms may remain in English.

---

# General Engineering Policy

Prefer simple and explicit implementations over unnecessary abstraction.

When evaluating code, consider:

- Separation of responsibilities
- Dependency direction
- Maintainability
- Extensibility
- Readability
- Unreal Engine conventions

Avoid recommending large-scale refactoring unless the current implementation
creates a concrete maintenance or runtime problem.

---

# Unreal Engine Review Policy

Review code with consideration for:

## UObject

- Lifetime
- Garbage Collection
- Ownership
- Delegate lifetime
- Reflection compatibility

## Actor Lifecycle

Consider:

- Constructor
- BeginPlay
- EndPlay
- PossessedBy
- UnPossessed
- Restart
- Respawn
- SetupPlayerInputComponent
- Component registration
- Repeated initialization

Assume lifecycle callbacks may execute more than once where Unreal Engine allows.

## Blueprint Integration

Verify:

- Blueprint-assigned references are validated.
- UPROPERTY specifiers are appropriate.
- Required assets cannot silently remain null.
- Runtime behavior does not unintentionally depend on Blueprint configuration.

When Blueprint assets cannot be inspected from a text diff, explicitly list the
manual verification items.

---

# C++ Review Policy

Review:

## API Design

- Const correctness
- Appropriate value/reference semantics
- Public API size
- Visibility
- Naming
- Interface quality

Prefer returning small scalar values by value.

Avoid unnecessary virtual functions or commented-out generated code.

---

## Includes

Review:

- Unnecessary includes
- Forward declarations
- Module dependencies
- Include order
- Generated header placement
- Relative include usage

---

## Performance

Report meaningful performance issues such as:

- Unnecessary Tick
- Repeated allocations
- Repeated expensive lookups
- Avoidable casts
- Frequent asset loading

Do not report insignificant micro-optimizations.

---

# Enhanced Input Review

When reviewing Enhanced Input code, verify:

- InputAction references
- InputMappingContext references
- Duplicate bindings
- Duplicate Mapping Context registration
- Ownership of Mapping Contexts
- Local Player assumptions
- Possession
- Respawn
- InputComponent reconstruction

Avoid assuming Player Index 0 unless explicitly justified.

---

# Gameplay Ability System Review

When reviewing GAS-related code, verify:

- AbilitySystemComponent initialization
- OwnerActor / AvatarActor setup
- Ability grants
- Gameplay Effects
- Gameplay Tags
- Prediction
- Replication
- Respawn
- Authority

Do not recommend introducing GAS unless it provides a concrete benefit.

Do not recommend modifying GAS core code unless no supported extension point exists.

---

# Review Policy

Review more than compilation errors.

Report:

- Confirmed runtime bugs
- Crash risks
- Unreal Engine lifecycle issues
- Incorrect ownership
- Invalid UObject lifetime assumptions
- Duplicate initialization
- Missing validation
- Design risks
- Maintainability concerns
- Meaningful performance issues
- Blueprint settings requiring manual verification

Classify findings as:

- Critical
- High
- Medium
- Low
- Suggestion

Clearly distinguish between:

- Confirmed bugs
- Design risks
- Optional improvements

Do not invent project requirements that are not present in:

- The source code
- The pull request description
- Existing project behavior
- Project documentation

---

# Review Output

Use the following structure.

## Summary

Explain:

- Purpose of the change
- Overall risk

## Findings

Sort findings by severity.

For each finding provide:

- Severity
- Location
- Confirmed bug or Design risk
- Explanation
- Failure condition
- Recommended fix

## Manual Verification

List Unreal Editor items that cannot be verified from the textual diff.

Examples:

- Blueprint settings
- Mapping Context
- Input Actions
- Asset assignments
- GameMode
- Pawn settings
- Component configuration
- Level configuration

## Optional Improvements

List non-blocking improvements separately.

If no Critical, High, or Medium issues exist, still report meaningful Low or
Suggestion items where appropriate.

Avoid responding only with:

> "Didn't find any major issues."

---

# Verification

For C++ changes, verify whenever possible:

- Header / Source consistency
- Unreal reflection compatibility
- Module dependencies
- Generated header placement
- Compilation risks

For gameplay changes, recommend only relevant manual verification.

Do not claim Blueprint or Unreal Editor behavior has been verified when only
textual source changes were reviewed.

Do not require unrelated project-wide testing for isolated changes.