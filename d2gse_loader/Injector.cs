using System;
using System.Runtime.InteropServices;
using System.Text;
using System.IO;
using d2gse_loader.WinAPI;

namespace d2gse_loader
{
    class Injector : IDisposable
    {
        private int processId = 0;
        IntPtr mainThread = IntPtr.Zero;
        IntPtr hProcess = IntPtr.Zero;
        string libraryName = string.Empty;
        IntPtr pAllocatedMemory = IntPtr.Zero;
        IntPtr hRemoteThread = IntPtr.Zero;
        int threadExitCode = 0;
        bool threadWorking = false;

        public void Dispose()
        {
            if (threadWorking)
                WaitForRemoteThread();

            Invoker.CloseHandle(hRemoteThread);
            Invoker.VirtualFreeEx(hProcess, pAllocatedMemory, libraryName.Length + 1, FreeType.Release);
            Invoker.CloseHandle(hProcess);
        }

        public void StartProcess(string filePath)
        {
            if (!File.Exists(filePath))
                throw new Exception("No such file");

            const uint CREATE_SUSPENDED = 0x00000004;
            const uint DETACHED_PROCESS = 0x00000008;

            PROCESS_INFORMATION pInfo = new PROCESS_INFORMATION();
            STARTUPINFO sInfo = new STARTUPINFO();
            SECURITY_ATTRIBUTES pSec = new SECURITY_ATTRIBUTES();
            SECURITY_ATTRIBUTES tSec = new SECURITY_ATTRIBUTES();
            pSec.nLength = Marshal.SizeOf(pSec);
            tSec.nLength = Marshal.SizeOf(tSec);

            if (!Invoker.CreateProcess(filePath, "",
                ref pSec, ref tSec, false, CREATE_SUSPENDED | DETACHED_PROCESS,
                IntPtr.Zero, null, ref sInfo, out pInfo))
                throw new Exception("Failed to create process");

            this.processId = pInfo.dwProcessId;
            this.mainThread = pInfo.hThread;
        }

        public void ResumeProcess()
        {
            if (mainThread == IntPtr.Zero)
                return;

            Invoker.ResumeThread(mainThread);
        }

        public void Inject(string libraryName)
        {
            if (!File.Exists(libraryName))
                throw new Exception("Patch file not found.");

            if (hProcess != IntPtr.Zero)
                throw new Exception("Already injected");

            hProcess = Invoker.OpenProcess(ProcessAccess.AllAccess, false, processId);
            if (hProcess == IntPtr.Zero)
                throw new Exception("Failed to open process for access");

            IntPtr hKernel32 = Invoker.GetModuleHandle("Kernel32");
            Console.WriteLine("kernel32 handle: {0}", hKernel32);

            this.libraryName = libraryName;

            pAllocatedMemory = Invoker.VirtualAllocEx(hProcess, IntPtr.Zero, libraryName.Length, AllocationType.Commit, AllocationProtect.PAGE_READWRITE);

            if (pAllocatedMemory == IntPtr.Zero)
                throw new Exception("Failed to allocate memory in remote process");

            Console.WriteLine("allocated memory address: {0}", pAllocatedMemory);

            int numBytes;
            if (!Invoker.WriteProcessMemory(hProcess, pAllocatedMemory, Encoding.ASCII.GetBytes(libraryName + '\0'), libraryName.Length + 1, out numBytes))
                throw new Exception("Failed to write in remote process memory");

            int threadId;
            hRemoteThread = Invoker.CreateRemoteThread(hProcess, IntPtr.Zero, 0,
                Invoker.GetProcAddress(hKernel32, "LoadLibraryA"), pAllocatedMemory, 0, out threadId);

            if (hRemoteThread == IntPtr.Zero)
                throw new Exception("Failed to start remote thread");

            threadWorking = true;
        }

        public int WaitForRemoteThread()
        {
            if (!threadWorking)
                throw new Exception("Not injected, nothing to wait for");

            if (Invoker.WaitForSingleObject(hRemoteThread, (uint)WaitResult.INFINITE) != WaitResult.WAIT_OBJECT_0)
                throw new Exception("Failed to wait for remote thread");

            threadWorking = false;

            if (!Invoker.GetExitCodeThread(hRemoteThread, out threadExitCode))
                throw new Exception("Failed to get thread exit code");

            Console.WriteLine("exit code: {0}", threadExitCode);
            Console.WriteLine(Marshal.GetLastWin32Error());
            if (threadExitCode == 0)
                throw new Exception("Failed to inject");

            threadWorking = false;
            return threadExitCode;
        }
    }
}
