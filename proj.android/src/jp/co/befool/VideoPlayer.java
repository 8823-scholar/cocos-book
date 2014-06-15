package jp.co.befool;

import co.jp.befool.book_cocos2d_x.R;

import org.cocos2dx.cpp.AppActivity;
import org.cocos2dx.lib.Cocos2dxActivity;

import java.io.IOException;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.res.AssetFileDescriptor;
import android.os.Bundle;
import android.media.MediaPlayer;
import android.view.SurfaceView;
import android.view.SurfaceHolder;
import android.view.ViewGroup;
import android.widget.RelativeLayout;
import android.widget.RelativeLayout.LayoutParams;
import android.util.Log;

public class VideoPlayer
    extends Activity
    implements SurfaceHolder.Callback, MediaPlayer.OnCompletionListener
{
    private MediaPlayer player;


    public static void play(String path)
    {
        Log.d("VideoPlayer", "play ==================================================");

        Context main = Cocos2dxActivity.getContext();
        Intent intent = new Intent();
        intent.setClass(main, VideoPlayer.class);
        intent.putExtra("path", path);
        main.startActivity(intent);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        Log.d("VideoPlayer", "onCreate ==============================================");
        super.onCreate(savedInstanceState);

        SurfaceView view = new SurfaceView(this);
        view.setLayoutParams(new ViewGroup.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT));
        SurfaceHolder holder = view.getHolder();
        holder.addCallback(this);
        holder.setType(SurfaceHolder.SURFACE_TYPE_PUSH_BUFFERS);

        RelativeLayout layout = new RelativeLayout(this);
        layout.setLayoutParams(new ViewGroup.LayoutParams(ViewGroup.LayoutParams.FILL_PARENT, ViewGroup.LayoutParams.FILL_PARENT));
        layout.addView(view, 0);
        this.setContentView(layout);
    }

    @Override
    public void surfaceCreated(SurfaceHolder holder)
    {
        Log.d("VideoPlayer", "surfaceCreated");

        this.player = new MediaPlayer();
        try {
            String path = this.getIntent().getStringExtra("path");
            AssetFileDescriptor afd = this.getAssets().openFd(path);
            Log.d("VideoPlayer", "length:" + afd.getLength());
            this.player.setDataSource(afd.getFileDescriptor(), afd.getStartOffset(), afd.getLength());
            //this.player.setDataSource(this, android.net.Uri.parse("android.resource://" + this.getPackageName() + "/" + R.raw.sample));
            this.player.setDisplay(holder);
            this.player.setOnCompletionListener(this);
            this.player.prepare();
            this.player.start();
        } catch (IOException e) {
            System.out.println("file not found.");
            return;
        }
    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height)
    {
        Log.d("VideoPlayer", "surfaceChanged");
    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder)
    {
        Log.d("VideoPlayer", "surfaceDestroyed");
    }

    @Override
    public void onCompletion(MediaPlayer player)
    {
        Log.d("VideoPlayer", "MediaPlayer.onCompletion");
        
        this.finish();
    }

    /*
    static {
        System.loadLibrary("cocos2dcpp");
    }
    */
}

