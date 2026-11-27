# libugmath.dll —— 从原始二进制复刻的 C++ 实现（证明包）

libugmath.dll 是 Siemens NX（本项目对应 NX 2412）的数学与几何基础库 DLL，NX 的建模、曲线曲面、网格等模块均链接它。

工业软件非常适合复刻下来作为科研学习的目标。本项目能证明复刻的还原度极高——能快速且完美地复刻其逻辑、还原代码。理论上，只要有几百万美金的算力，AutoCAD 也能两周之内复刻出来且能运行。

本包含 libugmath.dll 的完整 C++ 源码、构建脚本、预编译产物与验证工具。
任何人都可以：编译它、证明产物与原始 DLL 行为一致、并将其替换进 NX 正常使用。

复现指标：机器码一致率 **97.7%**（1712/1752——其中 5 个函数与原始机器码逐字节相同，1707 个重定位归一化后逐字节相同；其余 40 个行为等价、机器码因原始 DLL 的编译器子版本不可得而不可复现）；黄金测试用例与合成输入用例的一致覆盖率均为 **100%**（累计逾 12 万条黑盒/边界/NaN/合成输入用例，零失败）。

## 1. 如何编译

**环境要求**：Windows x64；Visual Studio 2022 Build Tools（或 VS 2019），需安装
"MSVC v142 - VS 2019 C++ x64/x86 生成工具"（14.29.x）与 Windows SDK 10.0.26100（或相近版本）。
构建脚本通过 `vswhere` 自动定位工具链；也可用环境变量 `UGMATH_MSVC_DIR` / `UGMATH_SDK_DIR` 指定安装目录。

**构建**（两步）：

```
cd build
python -I build_static.py     # 编译 src/ugmath 全部 C++ 源码
python -I build_link_r8.py    # 链接生成 out/libugmath.dll（及 .lib/.exp）
```

产物在 `build/out/`。`third_party/libsyss.def` 会在链接时自动生成 libsyss 导入库
（libsyss.dll 是 NX 自带依赖，不需要随包分发）。

**构建是确定性的**：重复构建除 PE 时间戳 4 字节（及 debug directory 中同一时间戳的副本
4 字节）外逐字节一致——这一点本身可被第 2 节的工具验证。

## 2. 如何证明与原始 DLL 一致

三项自检全部可复跑，`evidence/` 下存有本包的自检结果。

**① 源码可重建性**——证明 `bin/libugmath.dll` 就是本包源码编译出来的：

```
python -X utf8 tools/verify_rebuild.py
```

它把 `src/` + `build/` 复制到临时目录完整重建，然后与 `bin/libugmath.dll` 对比：
时间戳归一化后的文件 SHA256 相等、逐节（.text/.rdata/.data/.pdata/.reloc）相等、
导出表相等。本包自检结果：**PASS**（见 `evidence/rebuild_gate.txt`）。

**② 导出函数完全一致**——证明与原始 NX libugmath.dll 的接口一致：

```
python -X utf8 tools/verify_exports.py --raw <NX原始libugmath.dll> --new bin/libugmath.dll
```

逐项对比全部导出：名称（C++ mangled 精确串）、序号（ordinal）、缺失/多余清单。
本包自检结果：**1235/1235 导出完全一致（missing 0 / extra 0 / ordinal mismatch 0）**
（见 `evidence/verify_exports.json`）。也可以手动对照：`dumpbin /exports` 两个文件后 diff。

**③ 加载与调用冒烟**——证明产物可被系统加载并正常调用：

```
python -X utf8 tools/smoke_load.py --dll bin/libugmath.dll --nxbin "<NX安装目录>\NXBIN"
```

LoadLibrary 本 DLL，并按导出表实际调用一批代表函数（数学/几何/错误处理等）。
本包自检结果：**45/45 PASS**（见 `evidence/smoke_load.json`）。

> 更深入的逐函数机器码级比对属于复刻工程内部工具，不在本包内；结论摘要：
> 1752 个函数全部通过执行级行为差分（同输入下原始 DLL 与复刻 DLL 实际运行、输出逐字节对齐），
> 其中 1712 个同时达到机器码级等价（M1 逐字节相同 / M2 重定位归一化相同）。

## 3. 如何替换 NX 的 libugmath.dll

1. **备份**：把 `<NX安装目录>\NXBIN\libugmath.dll` 复制一份为 `libugmath.dll.orig`；
2. **替换**：用本包 `bin/libugmath.dll` 覆盖 `NXBIN\libugmath.dll`；
3. **自检**：先跑第 2 节的 ③（`--nxbin` 指向安装目录），确认加载 PASS；
4. **实机验证**：启动 NX，做常规操作——新建零件、草图、曲线、曲面/实体建模、
   网格与公差相关操作；行为应与原版一致；
5. **回退**：若发现异常，用 `libugmath.dll.orig` 覆盖回去即可恢复。

运行依赖与 NX 原版相同：NX 自带的 `libsyss.dll` 与 MSVC 运行库（14.29 系）。

## 目录结构

```
src/ugmath/{include,src}   纯 C++ 源码（去注释版，与 bin 严格同源）
build/                     构建脚本（两步构建 + 环境定位）
bin/                       预编译产物：libugmath.dll / .lib / .exp
tools/                     验证工具：verify_rebuild / verify_exports / smoke_load
third_party/               libsyss.def（链接用）
evidence/                  本包三项自检的结果文件
```

## 复刻概况

- 目标：NX 2412 的 `libugmath.dll`（原始 SHA256 见 `evidence/verify_exports.json` 内记录）
- 覆盖：1752 个函数（其中 1235 个导出）全部有执行级行为等价证据；构建链不使用任何汇编源文件，全部为 C++ 源码编译
- 构建产物：`bin/libugmath.dll`（SHA256 见 MANIFEST.sha256）

## 需要复刻工业软件
联系qq3388098982。工业内核复刻、工业软件复刻、代码语义注释、代码分类整理。
本项目的注释已经去掉，名字也略混淆。实际可还原。