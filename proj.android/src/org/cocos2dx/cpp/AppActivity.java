/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package org.cocos2dx.cpp;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.ActivityNotFoundException;
import android.content.Intent;
import android.content.res.AssetManager;
import android.net.Uri;
import android.os.Bundle;
import android.os.Environment;

public class AppActivity extends Cocos2dxActivity {
	// Buffer size used.
    private final static int BUFFER_SIZE = 1024;
	static Activity a;
	static File file = null;
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		a = this;
		super.onCreate(savedInstanceState);
	}
	public static void Charmy_Share() {
		  new Thread(new Runnable() {
		   public void run() {
			   if(file == null || !file.exists()){
				   CopyShareToSdCard();
				   file = new File(Environment.getExternalStorageDirectory().getAbsolutePath() + "/arkaflow.jpg");
			   }
			   Intent intent = new Intent(Intent.ACTION_SEND);
			   intent.setType("image/*");
			   intent.putExtra(Intent.EXTRA_SUBJECT, "Arkaflow");
			   intent.putExtra(Intent.EXTRA_TEXT, "Check out this extradinary game, Arkaflow! It's real fun! http://www.CharmySoft.com");
			   intent.putExtra(Intent.EXTRA_STREAM, 
					   Uri.fromFile(file));
			   a.startActivity(Intent.createChooser(intent, "Share Game")); 
		   }
		  }).start();
	}
	
	public static void Charmy_Rate(){
		Uri uri = Uri.parse("market://details?id=" + a.getApplicationContext().getPackageName());
		Intent goToMarket = new Intent(Intent.ACTION_VIEW, uri);
		try {
		  a.startActivity(goToMarket);
		} catch (ActivityNotFoundException e) {
		  a.startActivity(new Intent(Intent.ACTION_VIEW, Uri.parse("http://play.google.com/store/apps/details?id=" + a.getApplicationContext().getPackageName())));
		}
	}
	
    private static void CopyShareToSdCard() {
        try{
        AssetManager assetManager = a.getApplicationContext().getAssets();
        InputStream in = assetManager.open("share.jpg");   
        OutputStream out = new FileOutputStream(Environment.getExternalStorageDirectory().getAbsolutePath() + "/arkaflow.jpg");
        copyAssetFiles(in, out);
        in.close();
        in = null;
        out.flush();
        out.close();
        out = null;
        }catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (NullPointerException e) {
            e.printStackTrace();
        } catch (Exception e) {
            e.printStackTrace();
        }

    }
	

	private static void copyAssetFiles(InputStream in, OutputStream out) {
        try {
 
            byte[] buffer = new byte[BUFFER_SIZE];
            int read;
 
            while ((read = in.read(buffer)) != -1) {
                out.write(buffer, 0, read);
            }
 
            in.close();
            in = null;
            out.flush();
            out.close();
            out = null;
 
        } catch (IOException e) {
        } catch (NullPointerException e) {
            e.printStackTrace();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
	
}
